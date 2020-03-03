//
// @author   liyan
// @contact  lyan_dut@outlook.com
//
#pragma once
#ifndef MYGENETICFORRCPSP_POPULATION_H
#define MYGENETICFORRCPSP_POPULATION_H

#include "Chromosome.h"
#include "Instance.h"

class Population {
public:
	Population(int populationId, int populationSize, String filePathPspLib);

	String populationToString();

	int getBestFitness() { return bestFitness; }

	int getAverageFitness() { return averageFitness; }

	void updateGeneration(int delta) { generation += delta; }

	/**
	 * Decode all chromosomes with serial schedule generation scheme
	 * with activity list representation
	 */
	void serialScheduleGenerationSchemeActivityList();

	/**
	 * Evaluate and update fitness values (averageFitness, bestFitness, worstFitness)
	 */
	void evaluateFitness();

	/**
	 * One point crossover
	 * Select two parents with best fitness value
	 * and replace the two chromosomes with the lowest fitness value
	 * by two new offspring chromosomes
	 */
	void onePointCrossOver(int tabuRuns);

	/**
	 * Storer et al. (1992) Mutation of all chromosomes, except parent_1, parent_2, child_1, child_2
	 * @param epsilon
	 */
	void mutationRandomActivityList(double epsilon, int tabuRuns);

	void printFinalSchedule();

private:
	/**
	 * Sort listOfChromosomes by fitness value
	 */
	void sortByFitness();

	int getRandomNumberInRange(int min, int max);

	Vector<int> createChild(const Vector<int> &parent1, const Vector<int> &parent2, int crossOverPoint);

private:
	int populationId;
	int populationSize;
	int averageFitness;
	int bestFitness;
	int worstFitness;
	int generation;
	Vector<Chromosome> listOfChromosomes;
	Vector<Vector<int>> listOfTabuActivityList;
	int tabuOverflowCount;
	int scheduleCount;
	String filePathPspLib;
};

#endif // !MYGENETICFORRCPSP_POPULATION_H
