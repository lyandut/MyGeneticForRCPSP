//
// @author   liyan
// @contact  lyan_dut@outlook.com
//
#pragma once
#ifndef MYGENETICFORRCPSP_CHROMOSOME_H
#define MYGENETICFORRCPSP_CHROMOSOME_H

#include <cassert>
#include "Project.h"

class Chromosome : public Project {

public:
	Chromosome(int projectId = 0) : Project(projectId) {}

	int getProjectId() { return projectId; }

	void setProjectId(int id) { projectId = id; }

	int getCompletion() { return completion; }

	const Vector<Activity>& getListOfActivities() { return listOfActivities; }

	const Vector<int>& getActivityList() { return activityList; }

	void setActivityList(Vector<int> &list) { activityList = list; }

};

#endif // !MYGENETICFORRCPSP_CHROMOSOME_H
