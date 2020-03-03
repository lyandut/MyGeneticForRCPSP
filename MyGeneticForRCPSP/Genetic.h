//
// @author   liyan
// @contact  lyan_dut@outlook.com
//
#pragma once
#ifndef MYGENETICFORRCPSP_GENETIC_H
#define MYGENETICFORRCPSP_GENETIC_H

#include "Population.h"

class Genetic {
public:
	Genetic(String filePathPspLib) : filePathPspLib(filePathPspLib) {}

	void solveOnePoint(int populationSize, int generationLimit, double mutationEpsilon, int tabuRuns);

private:
	void printProgress(clock_t startTime, int current, int bestFitness, int averageFitness);

private:
	String filePathPspLib;
	double executionTime;
};

#endif // !MYGENETICFORRCPSP_GENETIC_H









