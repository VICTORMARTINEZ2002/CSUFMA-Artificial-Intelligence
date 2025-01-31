#ifndef AUXFUNC_H
	#define AUXFUNC_H

	#include <vector>

	// Function declarations
	double fitness(
	    const std::vector<std::vector<float>>& acessP, 
	    const std::vector<std::vector<float>>& people, 
	    const std::vector<int>& solucao
	);

	double meanDist(
	    const std::vector<std::vector<float>>& acessP, 
	    const std::vector<std::vector<float>>& people, 
	    const std::vector<int>& solucao
	);

	double sumDist(
	    const std::vector<std::vector<float>>& acessP, 
	    const std::vector<std::vector<float>>& people, 
	    const std::vector<int>& solucao
	);

	void acessPointDistribution(
	    const std::vector<std::vector<float>>& acessP, 
	    const std::vector<int>& solucao, 
	    std::vector<int>& contConect
	);

	int aboveLimt(
		const std::vector<std::vector<float>>& acessP,
		const std::vector<int>& solucao
	);

	int nonConect(const std::vector<int>& solucao);

	void printStatusSolution(
		const std::vector<std::vector<float>>& acessP,
		const std::vector<std::vector<float>>& people,
		const std::vector<int>& solucao
	);

#endif // AUXFUNC_H