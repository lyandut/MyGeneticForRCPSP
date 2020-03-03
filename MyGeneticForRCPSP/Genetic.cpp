//
// @author   liyan
// @contact  lyan_dut@outlook.com
//

#include <ctime>
#include "Genetic.h"

void Genetic::solveOnePoint(int populationSize, int generationLimit, double mutationEpsilon, int tabuRuns) {
	// Construct population
	Population population(1, populationSize, filePathPspLib);

	clock_t startTime = clock();
	population.serialScheduleGenerationSchemeActivityList();
	population.evaluateFitness();

	// Start algorithm
	for (int i = 0; i < generationLimit; ++i) {
		clock_t currStartTime = clock();

		// Increment generation
		population.updateGeneration(1);

		// One point crossover
		population.onePointCrossOver(tabuRuns);

		// Mutation random activity list
		population.mutationRandomActivityList(mutationEpsilon, tabuRuns);

		// Decode and evaluate
		population.serialScheduleGenerationSchemeActivityList();
		population.evaluateFitness();

		printProgress(currStartTime, i + 1, population.getBestFitness(), population.getAverageFitness());
	}

	executionTime = clock() - startTime / static_cast<double>(CLOCKS_PER_SEC);

	// Print final schedule
	population.printFinalSchedule();

	std::cout << "CPU time (sec.):        " << executionTime << std::endl;
}

void Genetic::printProgress(clock_t startTime, int current, int bestFitness, int averageFitness) {
	std::cout << "Generations: " << current
		<< ", Execution time: " << (clock() - startTime) / static_cast<double>(CLOCKS_PER_SEC)
		<< ", Best fitness: " << bestFitness
		<< ", Average fitness: " << averageFitness << std::endl;
}

