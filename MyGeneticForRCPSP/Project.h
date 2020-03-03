#pragma once
#ifndef MYGENETICFORRCPSP_PROJECT_H
#define MYGENETICFORRCPSP_PROJECT_H

#include "Activity.h"
#include "Resource.h"

class Project {
	friend void readPspLibInstance(Project &proj, const char *filePath);

public:
	Project(int projectId = 0) : projectId(projectId) {}

	/**
	 * Generates full project report
	 * @return String that contains project information
	 */
	String projectToString();

	/**
	 * Generates a precedence feasible activity list
	 * and sets activity object variable: activityListPosition
	 */
	void randomActivityList();
	void setActivityListPosByActivityList();

	/**
	 * Serial schedule generator scheme with activity list representation
	 */
	void serialScheduleGeneratorSchemeActivityList();

private:
	/**
	 * Resets instance variables
	 */
	void resetSchedule();

	/**
	 * Sets instance variables and returns list of activity indices
	 * @return List of eligible activities / activity indices
	 */
	Vector<int> getEligibleActivityIndices();

	/**
	 * Set activity sequence
	 */
	void setActivitySequence(Activity &activity, int sequencePosition);

	/**
	 * Set earliest precedence feasible start
	 */
	void setEarliestPrecedenceFeasibleStart(Activity &activity);

	/**
	 * Set earliest resource feasible start between earliestStart and planningHorizon
	 */
	void setEarliestResourceFeasibleStart(Activity &activity);

	/**
	 * Set resource consumption of activity according to start period
	 */
	void setResourceConsumption(Activity &activity);

protected:
	int projectId;
	Vector<Activity> listOfActivities;
	Vector<Resource> listOfResources;
	Time dueDate;
	Time completion;
	Time planningHorizon;
	Vector<int> activityList;
	Vector<int> activitySequence;
};

#endif // !MYGENETICFORRCPSP_PROJECT_H









