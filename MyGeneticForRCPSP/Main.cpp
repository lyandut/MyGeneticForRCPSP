//
// @author   liyan
// @contact  lyan_dut@outlook.com
//

#include <iostream>
#include "Genetic.h"

int main(int argc, char *argv[]) {

	// Create instance of genetic algorithm
	Genetic geneticAlgorithm("Instance/j30/j301_1.sm");

	// Genetic algorithm with one point cross over, random activity list mutation and tabu list
	geneticAlgorithm.solveOnePoint(200, 100, 0.4, 100);

	system("PAUSE");
	return 0;

}
