//
// @author   liyan
// @contact  lyan_dut@outlook.com
//

#include <cstdlib>
#include <ctime>
#include <cassert>
#include "Project.h"

String Project::projectToString() {
	std::ostringstream oss;

	for (Activity &activity : listOfActivities) {
		oss << activity.activityToString();
	}

	for (Resource &resource : listOfResources) {
		oss << resource.resourceToString();
		oss << resource.resourceProfileToString(50) << "\n\n";
	}

	oss << "Project:       " << projectId << "\n"
		<< "Due date:      " << dueDate << "\n"
		<< "Completion:    " << completion << "\n"
		<< "Activity list: " << activityList << "\n\n";

	return oss.str();
}

void Project::randomActivityList() {
	// Reset all necessary variables
	resetSchedule();

	// Set random seed
	srand(NULL);

	// Create new random activity list
	Vector<int> tmpActivityList(listOfActivities.size(), 0);
	Vector<bool> selectedIndices(listOfActivities.size(), false);
	for (int i = 0; i < listOfActivities.size(); ++i) {
		Vector<int> eligibleActivityIndices = getEligibleActivityIndices();
		int choice = eligibleActivityIndices[rand() % eligibleActivityIndices.size()];
		while (selectedIndices[choice]) {
			choice = eligibleActivityIndices[rand() % eligibleActivityIndices.size()];
		}
		selectedIndices[choice] = true;
		listOfActivities[choice].setScheduled(true);
		listOfActivities[choice].setEligible(false);
		tmpActivityList[i] = listOfActivities[choice].getActivityId();
	}

	resetSchedule();
	activityList = std::move(tmpActivityList);
}

void Project::setActivityListPosByActivityList() {
	for (int i = 0; i < activityList.size(); ++i) {
		int activityId = activityList[i];
		assert(activityId == listOfActivities[activityId - 1].getActivityId());
		listOfActivities[activityId - 1].setActivityListPosition(i);
	}
}

void Project::serialScheduleGeneratorSchemeActivityList() {
	// Reset all necessary values
	resetSchedule();

	// Loop through all activities
	for (int i = 0; i < listOfActivities.size(); ++i) {

		// Select eligible activity by activity list position
		Vector<int> eligibleActivityIndices = getEligibleActivityIndices();
		auto selectedIterator = std::min_element(eligibleActivityIndices.begin(), eligibleActivityIndices.end(),
			[this](int lhs, int rhs) {
			return listOfActivities[lhs].getActivityListPosition() < listOfActivities[rhs].getActivityListPosition();
		});
		Activity &selectedActivity = listOfActivities[*selectedIterator];

		// Set activity sequence
		setActivitySequence(selectedActivity, i);

		// Calculate and set earliest start
		setEarliestPrecedenceFeasibleStart(selectedActivity);

		// Calculate and set earliest resource feasible start
		setEarliestResourceFeasibleStart(selectedActivity);

		// Set finish
		selectedActivity.setFinish(selectedActivity.getStart() + selectedActivity.getDuration());

		// Set scheduled flag
		selectedActivity.setScheduled(true);

		// Set resource
		setResourceConsumption(selectedActivity);
	}

	// Set completion
	completion = listOfActivities[activitySequence.back() - 1].getFinish();
}

void Project::resetSchedule() {
	for (Activity &activity : listOfActivities) {
		activity.resetActivity();
	}
	for (Resource &resource : listOfResources) {
		resource.resetResourceProfile();
	}
}

Vector<int> Project::getEligibleActivityIndices() {
	Vector<int> eligibleActivityIndices;
	eligibleActivityIndices.reserve(listOfActivities.size());
	for (int i = 0; i < listOfActivities.size(); ++i) {
		Activity &currentActivity = listOfActivities[i];
		if (!currentActivity.isScheduled()) {
			currentActivity.setEligible(true);
			if (currentActivity.getPredecessors().empty()) {
				eligibleActivityIndices.push_back(i);
			}
			else {
				for (int predecessor : currentActivity.getPredecessors()) {
					if (!listOfActivities[predecessor - 1].isScheduled()) {
						currentActivity.setEligible(false);
					}
				}
				if (currentActivity.isEligible()) {
					eligibleActivityIndices.push_back(i);
				}
			}
		}
	}
	return eligibleActivityIndices;
}

void Project::setActivitySequence(Activity &selectedActivity, int sequencePosition) {
	activitySequence[sequencePosition] = selectedActivity.getActivityId();
}

void Project::setEarliestPrecedenceFeasibleStart(Activity &selectedActivity) {
	Time earliestStart = 0;
	for (int predecessor : selectedActivity.getPredecessors()) {
		earliestStart = std::max(earliestStart, listOfActivities[predecessor - 1].getFinish());
	}
	selectedActivity.setEarliestStart(earliestStart);
}

void Project::setEarliestResourceFeasibleStart(Activity &selectedActivity) {
	// Skip if dummy activity
	if (selectedActivity.getDuration() == 0) {
		selectedActivity.setStart(selectedActivity.getEarliestStart());
	}

	// Boolean resource feasible
	bool feasible = false;

	// For each period `i` from earliestStart to planningHorizon
	for (int i = selectedActivity.getEarliestStart(); i <= planningHorizon - selectedActivity.getDuration(); ++i) {
		// Check for each resource, feasibility from period `i` to period `i + duration` of activity
		for (Resource &currentResource : listOfResources) {
			for (int j = i; j < i + selectedActivity.getDuration(); ++j) {
				if (selectedActivity.getConsumptions()[currentResource.getResourceId() - 1] +
					currentResource.getResourceProfile()[j] <=
					currentResource.getResourceUpperBound()) {
					feasible = true;
				}
				else {
					// If one resource-period-combination is not feasible, break
					feasible = false;
					break;
				}
			}
			if (!feasible) { break; }
		}

		// Check if current period `i` is resource feasible
		if (feasible) {
			selectedActivity.setStart(i);
			break;
		}
	}
}

void Project::setResourceConsumption(Activity &selectedActivity) {
	// For each resource
	for (Resource &currentResource : listOfResources) {
		if (selectedActivity.getConsumptions()[currentResource.getResourceId() - 1] != 0) {
			// For periods `i` between start and finish of activity
			for (int i = selectedActivity.getStart(); i < selectedActivity.getFinish(); ++i) {
				currentResource.updateResourceProfile(
					i, selectedActivity.getConsumptions()[currentResource.getResourceId() - 1]
				);
			}
		}
	}
}