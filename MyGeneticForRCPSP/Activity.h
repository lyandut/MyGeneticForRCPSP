#pragma once
#ifndef MYGENETICFORRCPSP_ACTIVITY_H
#define MYGENETICFORRCPSP_ACTIVITY_H

#include "Common.h"

class Activity {
public:
	Activity(int activityId, int mode, const Vector<int> &successors, const Vector<int> &predecessors,
		int duration, const Vector<int> &consumptions, int numberSuccessors) :
		activityId(activityId), mode(mode), successors(successors), predecessors(predecessors),
		duration(duration), consumptions(consumptions), numberSuccessors(numberSuccessors) {}

	String activityToString() {
		std::ostringstream oss;
		oss << "Activity:          " << activityId << "\n"
			<< "Activity list pos: " << activityListPosition << "\n"
			<< "Duration:          " << duration << "\n"
			<< "Consumption:       " << consumptions << "\n"
			<< "Predecessors:      " << predecessors << "\n"
			<< "Successors         " << successors << "\n"
			<< "Start:             " << start << "\n"
			<< "Finish:            " << finish << "\n"
			<< "Earliest start:    " << earliestStart << "\n"
			<< "Earliest finish:   " << earliestFinish << "\n"
			<< "Latest start:      " << latestStart << "\n"
			<< "Latest finish:     " << latestFinish << "\n"
			<< "Scheduled:         " << scheduled << "\n"
			<< "Eligible:          " << eligible << "\n\n";
		return oss.str();
	}

	void resetActivity() {
		eligible = false;
		scheduled = false;
		start = 0;
		finish = 0;
		earliestStart = 0;
		earliestFinish = 0;
		latestStart = 0;
		latestFinish = 0;
	}

	int getActivityId() { return activityId; }

	const Vector<int>& getSuccessors() { return successors; }

	const Vector<int>& getPredecessors() { return predecessors; }

	int getDuration() { return duration; }

	const Vector<int>& getConsumptions() { return consumptions; }

	Time getStart() { return start; }

	void setStart(Time t) { start = t; }

	Time getFinish() { return finish; }

	void setFinish(Time t) { finish = t; }

	Time getEarliestStart() { return earliestStart; }

	void setEarliestStart(Time t) { earliestStart = t; }

	Time getEarliestFinish() { return earliestFinish; }

	void setEarliestFinish(Time t) { earliestFinish = t; }

	Time getLatestStart() { return latestStart; }

	void setLatestStart(Time t) { latestStart = t; }

	Time getLatestFinish() { return latestFinish; }

	void setLatestFinish(Time t) { latestFinish = t; }

	bool isScheduled() { return scheduled; }

	void setScheduled(bool flag) { scheduled = flag; }

	bool isEligible() { return eligible; }

	void setEligible(bool flag) { eligible = flag; }

	int getActivityListPosition() { return activityListPosition; }

	void setActivityListPosition(int pos) { activityListPosition = pos; }

private:
	// Activity id
	int activityId;
	// Activity mode
	int mode;
	// Number of successors
	int numberSuccessors;
	// List of successors
	Vector<int> successors;
	// List of predecessors
	Vector<int> predecessors;
	// Activity duration
	int duration;
	// Activity consumptions
	Vector<int> consumptions;
	// Activity's start
	Time start;
	// Activity's earliest finish
	Time finish;
	// Activity's earliest start
	Time earliestStart;
	// Activity's earliest finish
	Time earliestFinish;
	// Activity's latest start
	Time latestStart;
	// Activity's latest finish
	Time latestFinish;
	// Activity scheduled
	bool scheduled;
	// Activity eligible
	bool eligible;
	// Activity list position
	int activityListPosition;
};


#endif // !MYGENETICFORRCPSP_ACTIVITY_H
