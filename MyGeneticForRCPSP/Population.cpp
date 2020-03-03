//
// @author   liyan
// @contact  lyan_dut@outlook.com
//

#include "Population.h"

Population::Population(int populationId, int populationSize, String filePathPspLib) :
	populationId(populationId), populationSize(populationSize), generation(0),
	listOfTabuActivityList(Vector<Vector<int>>()),
	tabuOverflowCount(0), scheduleCount(0), filePathPspLib(filePathPspLib) {
	// Init list of chromosomes
	Vector<Chromosome> tmpListOfChromosomes;
	tmpListOfChromosomes.reserve(populationSize);
	for (int i = 0; i < populationSize; ++i) {
		Chromosome chromosome(i + 1);
		readPspLibInstance(chromosome, filePathPspLib.c_str());
		tmpListOfChromosomes.push_back(chromosome);
	}
	listOfChromosomes = std::move(tmpListOfChromosomes);

	// Set random seed
	srand(NULL);
}

String Population::populationToString() {
	std::ostringstream oss;
	oss << "Generation:      " << generation << "\n"
		<< "Population size: " << populationSize << "\n"
		<< "Best fitness:    " << bestFitness << "\n"
		<< "Worst fitness:   " << worstFitness << "\n"
		<< "Average fitness: " << averageFitness << "\n\n";
	return oss.str();
}

void Population::serialScheduleGenerationSchemeActivityList() {
	for (Chromosome &chromosome : listOfChromosomes) {
		chromosome.serialScheduleGeneratorSchemeActivityList();
		scheduleCount += 1;
	}
}

void Population::evaluateFitness() {
	sortByFitness();
	bestFitness = listOfChromosomes.front().getCompletion();
	worstFitness = listOfChromosomes.back().getCompletion();
	int sumCompletion = 0;
	for (Chromosome &chromosome : listOfChromosomes) {
		sumCompletion += chromosome.getCompletion();
	}
	averageFitness = sumCompletion / listOfChromosomes.size();
}

void Population::onePointCrossOver(int tabuRuns) {
	// Select parents / activityLists
	auto &parent1 = listOfChromosomes[getRandomNumberInRange(0, 1)].getActivityList();
	auto &parent2 = listOfChromosomes[getRandomNumberInRange(2, 4)].getActivityList();

	// Create children
	for (int i = 0; i < tabuRuns; ++i) {
		// Select random point
		int point = rand() % parent1.size();
		Vector<int> child1 = createChild(parent1, parent2, point);
		Vector<int> child2 = createChild(parent2, parent1, point);
		if (std::find(listOfTabuActivityList.begin(), listOfTabuActivityList.end(),
			child1) == listOfTabuActivityList.end()) {
			// Add to tabuList
			listOfTabuActivityList.push_back(child1);
			listOfTabuActivityList.push_back(child2);
			break;
		}
		if (i == tabuRuns - 1) {
			tabuOverflowCount += 1;
		}
	}

	// Update chromosomes with lowest fitness
	int maxProjectId = (*std::max_element(listOfChromosomes.begin(), listOfChromosomes.end(),
		[](Chromosome &lhs, Chromosome &rhs) { return lhs.getProjectId() < rhs.getProjectId(); })
		).getProjectId();
	(*(listOfChromosomes.end() - 2)).setProjectId(maxProjectId + 1);
	(*(listOfChromosomes.end() - 2)).setActivityList(*(listOfTabuActivityList.end() - 2));
	(*(listOfChromosomes.end() - 2)).setActivityListPosByActivityList();
	(*(listOfChromosomes.end() - 1)).setProjectId(maxProjectId + 2);
	(*(listOfChromosomes.end() - 1)).setActivityList(*(listOfTabuActivityList.end() - 1));
	(*(listOfChromosomes.end() - 1)).setActivityListPosByActivityList();
}

void Population::mutationRandomActivityList(double epsilon, int tabuRuns) {
	sortByFitness();
	for (int i = listOfChromosomes.size() / 2; i < listOfChromosomes.size() - 3; ++i) {
		if ((rand() % 100) * 0.01 > epsilon) {
			// Update Id
			int maxProjectId = (*std::max_element(listOfChromosomes.begin(), listOfChromosomes.end(),
				[](Chromosome &lhs, Chromosome &rhs) { return lhs.getProjectId() < rhs.getProjectId(); })
				).getProjectId();
			listOfChromosomes[i].setProjectId(maxProjectId + 1);

			// Add to tabu list
			listOfTabuActivityList.push_back(listOfChromosomes[i].getActivityList());

			// Tabu runs
			for (int j = 0; j < tabuRuns; ++j) {
				listOfChromosomes[i].randomActivityList();
				if (std::find(listOfTabuActivityList.begin(), listOfTabuActivityList.end(),
					listOfChromosomes[i].getActivityList()) == listOfTabuActivityList.end()) {
					break;
				}
				if (j == tabuRuns - 1) {
					tabuOverflowCount += 1;
				}
			}

			listOfChromosomes[i].setActivityListPosByActivityList();
		}
	}
}

void Population::printFinalSchedule() {
	// printBestSchedule
	sortByFitness();
	std::cout << listOfChromosomes[0].projectToString();
	// printScheduleCount
	std::cout << "Schedule count:         " << scheduleCount << std::endl;
	std::cout << "PSPLIP instance:        " << filePathPspLib << std::endl;
	// printTabuOverflowCount
	std::cout << "Tabu overflow count:    " << tabuOverflowCount << std::endl;
}

void Population::sortByFitness() {
	std::sort(listOfChromosomes.begin(), listOfChromosomes.end(),
		[](Chromosome &lhs, Chromosome &rhs) { return lhs.getCompletion() < rhs.getCompletion(); });
}

int Population::getRandomNumberInRange(int min, int max) {
	if (min >= max) {
		int tmp = min;
		min = max;
		max = tmp;
	}
	return rand() % ((max - min) + 1) + min;
}

Vector<int> Population::createChild(const Vector<int>& parent1, const Vector<int>& parent2, int crossOverPoint) {
	Vector<int> child(parent1.begin(), parent1.begin() + crossOverPoint);
	for (int activityId : parent2) {
		if (std::find(child.begin(), child.end(), activityId) == child.end()) {
			child.push_back(activityId);
		}
	}
	return child;
}
