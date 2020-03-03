#pragma once
#pragma once
#ifndef MYGENETICFORRCPSP_INSTANCE_H
#define MYGENETICFORRCPSP_INSTANCE_H

#include <fstream>
#include <regex>
#include <cstring>
#include "Project.h"

/**
 * Skip n line in ifstream
 * @param ifs
 * @param numberLines
 */
static void skip(std::ifstream &ifs, String &str, int numberLines = 0) {
	for (int i = 0; i <= numberLines; ++i) {
		std::getline(ifs, str); //skip
	}
}

/**
 * Read instance of PSPLib and pass data to project object
 * @param filePath PspLibFile
 */
static void readPspLibInstance(Project &proj, const char *filePath) {
	std::ifstream infile(filePath);
	if (!infile) { return; }

	String line;
	std::regex pattern(".*?(-?\\d+).*?");
	std::smatch sm;

	// Number of activities
	skip(infile, line, 5);
	int numberActivities = 0;
	if (std::regex_match(line, sm, pattern)) {
		numberActivities = std::stoi(sm[1]);
	}

	// Planning horizon
	skip(infile, line);
	if (std::regex_match(line, sm, pattern)) {
		proj.planningHorizon = std::stoi(sm[1]);
	}

	// Number of resources
	skip(infile, line, 1);
	int numberResources = 0;
	if (std::regex_match(line, sm, pattern)) {
		numberResources = std::stoi(sm[1]);
	}

	// Due date
	skip(infile, line, 4);
	for (int i = 0; i < 4; ++i) {
		infile >> proj.dueDate;
	}

	// Lists for activity objects
	skip(infile, line, 3);
	Vector<int> activityId(numberActivities);
	Vector<int> activityMode(numberActivities);
	Vector<int> numberSuccessors(numberActivities);
	Vector<Vector<int>> successors(numberActivities);
	Vector<Vector<int>> predecessors(numberActivities);

	for (int i = 0; i < numberActivities; ++i) {
		infile >> activityId[i] >> activityMode[i] >> numberSuccessors[i];
		if (numberSuccessors[i]) {
			successors[i].resize(numberSuccessors[i]);
			for (int k = 0; k < numberSuccessors[i]; ++k) {
				// Set successors
				infile >> successors[i][k];
				// Set predecessors
				predecessors[successors[i][k] - 1].push_back(activityId[i]);
			}
		}
	}

	// Set duration and consumption
	skip(infile, line, 4);
	Vector<int> duration(numberActivities);
	Vector<Vector<int>> consumption(numberActivities);
	for (int i = 0; i < numberActivities; ++i) {
		for (int k = 0; k < 3; ++k) {
			infile >> duration[i];
		}
		Vector<int> tmpConsumption(numberResources);
		for (int k = 0; k < numberResources; ++k) {
			infile >> tmpConsumption[k];
		}
		consumption[i] = std::move(tmpConsumption);
	}

	// Create list of activity objects
	Vector<Activity> tmpListOfActivities;
	tmpListOfActivities.reserve(numberActivities);
	for (int i = 0; i < numberActivities; ++i) {
		tmpListOfActivities.emplace_back(
			activityId.at(i),
			activityMode.at(i),
			successors.at(i),
			predecessors.at(i),
			duration.at(i),
			consumption.at(i),
			numberSuccessors.at(i)
		);
	}
	proj.listOfActivities = std::move(tmpListOfActivities);

	// Set resources
	skip(infile, line, 3);
	int resourceAvailablity = 0;
	Vector<Resource> tmpResourceList;
	tmpResourceList.reserve(numberResources);
	for (int i = 0; i < numberResources; ++i) {
		infile >> resourceAvailablity;
		tmpResourceList.emplace_back(i + 1, resourceAvailablity, proj.planningHorizon);
	}
	proj.listOfResources = std::move(tmpResourceList);

	// set random precedence feasible activity list
	proj.randomActivityList();
	proj.setActivityListPosByActivityList();

	// Set empty activity sequence
	proj.activitySequence = std::move(Vector<int>(numberActivities, 0));

	infile.close();
}

#endif // !MYGENETICFORRCPSP_INSTANCE_H