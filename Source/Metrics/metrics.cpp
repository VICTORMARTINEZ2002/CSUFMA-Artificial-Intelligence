#include <vector>
#include <cmath>

// Imagine a lot of metric functions :)

double euclideanMetric(std::vector<std::vector<float>> acessP, std::vector<std::vector<float>> people, int a, int p){
	if(a==-1){return 0;}
	double dist=0;
	int dim = acessP[0].size()-1;
	for(int i=0; i<=dim-1; i++){
		dist += pow(acessP[a][i]-people[p][i], 2);
	}
	return sqrt(dist);
}