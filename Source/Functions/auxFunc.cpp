#include <stdio.h>

#include <cmath>
#include <vector>
#include <iostream>

#include "../Metrics/Metrics.h"

using namespace std;

// Declarações
int aboveLimt(const vector<vector<float>>& acessP, const vector<int>& solucao){
	vector<int> contConect(acessP.size(), 0);
	for(size_t i=0; i<=solucao.size()-1; i++){
		if(solucao[i]!=-1){contConect[solucao[i]]++;}
	}
	int sum=0;
	for(size_t i=0; i<=contConect.size()-1; i++){
		int lim = (int)acessP[i][acessP[0].size()-1];
		sum += max(0, contConect[i] - lim);
	} return sum;
}


double fitness(const vector<vector<float>>& acessP, const vector<vector<float>>& people, const vector<int>& solucao){
	int notConect=0;
	double  max_dist = 0;
	double mean_dist = 0;
	vector<int> contConect(acessP.size(), 0);

	// Calculo Mean Distancias
	for(size_t i=0; i<=solucao.size()-1; i++){
		if(solucao[i]!=-1){
			contConect[solucao[i]]++;
			double d = euclideanMetric(acessP, people, solucao[i], i);
			if(d>max_dist){max_dist=d;}
			mean_dist += d;
		}else{notConect++;}
	}
	int sum=0;
	for(size_t i=0; i<=contConect.size()-1; i++){
		int lim = (int)acessP[i][acessP[0].size()-1];
		sum += max(0, contConect[i] - lim);
	}

	// Penalizar Não Conectados
	double penl_nConetado = notConect * (max_dist+10);
	
	// Penalizar Violação Limite
	double penl_Limite = (3*max_dist) * sum;
	
	return (mean_dist+penl_nConetado+penl_Limite)/solucao.size();
}



double meanDist(const vector<vector<float>>& acessP, const vector<vector<float>>& people, const vector<int>& solucao){
	int cont=0;
	double dist = 0;
	for(size_t i=0; i<=solucao.size()-1; i++){
		dist += euclideanMetric(acessP, people, solucao[i], i);;
		cont++;
	}
	return dist/cont;
}

double sumDist(const vector<vector<float>>& acessP, const vector<vector<float>>& people, const vector<int>& solucao){
	double dist = 0;
	for(size_t i=0; i<=solucao.size()-1; i++){
		dist += euclideanMetric(acessP, people, solucao[i], i);;
	}
	return dist;
}

void acessPointDistribution(const vector<vector<float>>& acessP, const vector<int>& solucao, vector<int>& contConect){
	contConect.resize(acessP.size(), 0);
	for(size_t i=0; i<=solucao.size()-1; i++){
		if(solucao[i]!=-1){contConect[solucao[i]]++;}
	}
}


int nonConect(const vector<int>& solucao){
	int cont = 0;
	for(size_t i=0; i<=solucao.size()-1; i++){
		if(solucao[i]==-1){cont++;}
	}
	return cont;
}

// ---------------------------------------------
void printStatusSolution(const vector<vector<float>>& acessP, const vector<vector<float>>& people, const vector<int>& solucao){
	printf("\nFitness = %lf\n",   fitness(acessP,people,solucao) );
	printf("Dist Mean = %lf\n",   meanDist(acessP,people,solucao));
	printf("nonConect = %d\n", nonConect(solucao)             );
	printf("aboveLimt = %d\n", aboveLimt(acessP,solucao)      );
	vector<int> contConect;     acessPointDistribution(acessP, solucao, contConect);

	cout << "Conections Distribution: ";
	for(size_t i=0; i<=contConect.size()-1; i++){cout << contConect[i] << " ";}
	cout << endl;
}
