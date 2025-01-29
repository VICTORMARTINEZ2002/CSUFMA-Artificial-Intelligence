#ifndef FITNESS_H
	#define FITNESS_H

	#include <vector>
	using namespace std;

	double  fitness(vector<vector<float>> acessP, vector<vector<float>> people, vector<int> solucao);
	double meanDist(vector<vector<float>> acessP, vector<vector<float>> people, vector<int> solucao);
	double  sumDist(vector<vector<float>> acessP, vector<vector<float>> people, vector<int> solucao);
	vector<int> acessPointDistribution(vector<vector<float>> acessP, vector<int> solucao);
	int   aboveLimt(vector<vector<float>> acessP, vector<int> solucao);
	int   nonConect(vector<int> solucao);

	

#endif // FITNESS_H
