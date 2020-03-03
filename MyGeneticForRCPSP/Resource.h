#pragma once
#ifndef MYGENETICFORRCPSP_RESOURCE_H
#define MYGENETICFORRCPSP_RESOURCE_H

#include "Common.h"

class Resource {
public:
	Resource(int resourceId, int resourceUpperBound, int planningHorizon) :
		resourceId(resourceId), resourceUpperBound(resourceUpperBound), resourceLowerBound(0),
		planningHorizon(planningHorizon), resourceProfile(planningHorizon, 0) {}

	String resourceToString() {
		std::ostringstream oss;
		oss << "Resource:             " << resourceId << "\n"
			<< "Resource upper bound: " << resourceUpperBound << "\n";
		return oss.str();
	}

	String resourceProfileToString(int toPeriod) {
		std::ostringstream oss;
		oss << Vector<int>(resourceProfile.begin(), resourceProfile.begin() + toPeriod);
		return oss.str();
	}

	void resetResourceProfile() {
		resourceProfile.assign(planningHorizon, 0);
	}

	int getResourceId() { return resourceId; }

	const Vector<int>& getResourceProfile() { return resourceProfile; }

	void setResourceProfile(Time period, int newProfile) { resourceProfile[period] = newProfile; }

	void updateResourceProfile(Time period, int delta) { 
		if (resourceProfile[period] + delta > resourceUpperBound) {
			std::cout << "Error" << std::endl;
		}
		resourceProfile[period] += delta;
	}

	int getResourceUpperBound() { return resourceUpperBound; }

	int getResourceLowerBound() { return resourceLowerBound; }

	Time getPlanningHorizon() { return planningHorizon; }

private:
	// Resource id
	int resourceId;
	// Resource profile list with variable length / periods
	Vector<int> resourceProfile;
	// Resource upper bound
	int resourceUpperBound;
	// Resource lower bound
	int resourceLowerBound;
	// Planning horizon
	Time planningHorizon;
};

#endif // !MYGENETICFORRCPSP_RESOURCE_H
