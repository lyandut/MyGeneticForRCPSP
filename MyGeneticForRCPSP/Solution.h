#pragma once
#ifndef MYGENETICFORRCPSP_SOLUTION_H
#define MYGENETICFORRCPSP_SOLUTION_H

#include "Common.h"

class Solution {
public:
	Solution() {}


private:
	// Solution id
	int solutionId;
	// List of activity objects
	List listOfActivities;
	// activity list representation
	Vector<int> activityList;
	// Random key representation
	Vector<int> randomKey;
	// Problem upper bound
	int upperBound;
	// Problem lower bound
	int lowerBound;
	// Fitness
	int fitness;
};

#endif // !MYGENETICFORRCPSP_SOLUTION_H


public class Solution {

	

	public Solution(int solutionId, List listOfActivities, int[] activityList, int[] randomKey, int upperBound, int lowerBound, int fitness) {

		this.solutionId = solutionId;
		this.listOfActivities = listOfActivities;
		this.activityList = activityList;
		this.randomKey = randomKey;
		this.upperBound = upperBound;
		this.lowerBound = lowerBound;
		this.fitness = fitness;
	}

	@Override
		public String toString() {
		return "Solution{" +
			"solutionId=" + solutionId +
			", listOfActivities=" + listOfActivities +
			", activityList=" + Arrays.toString(activityList) +
			", randomKey=" + Arrays.toString(randomKey) +
			", upperBound=" + upperBound +
			", lowerBound=" + lowerBound +
			", fitness=" + fitness +
			'}';
	}

	public int getSolutionId() {
		return solutionId;
	}

	public void setSolutionId(int solutionId) {
		this.solutionId = solutionId;
	}

	public List getListOfActivities() {
		return listOfActivities;
	}

	public void setListOfActivities(List listOfActivities) {
		this.listOfActivities = listOfActivities;
	}

	public int[] getActivityList() {
		return activityList;
	}

	public void setActivityList(int[] activityList) {
		this.activityList = activityList;
	}

	public int[] getRandomKey() {
		return randomKey;
	}

	public void setRandomKey(int[] randomKey) {
		this.randomKey = randomKey;
	}

	public int getUpperBound() {
		return upperBound;
	}

	public void setUpperBound(int upperBound) {
		this.upperBound = upperBound;
	}

	public int getLowerBound() {
		return lowerBound;
	}

	public void setLowerBound(int lowerBound) {
		this.lowerBound = lowerBound;
	}

	public int getFitness() {
		return fitness;
	}

	public void setFitness(int fitness) {
		this.fitness = fitness;
	}

}
