#include <vector>
#include <cmath>
#include <iostream>
#include "../Metrics/Metrics.h"
using namespace std;

// Declarações
int aboveLimt(vector<vector<float>>, vector<int>);

double fitness(vector<vector<float>> acessP, vector<vector<float>> people, vector<int> solucao){
	int notConect=0;
	double  max_dist = 0;
	double mean_dist = 0;
	std::vector<int> contConect(acessP.size(), 0);

	// Calculo Mean Distancias
	for(size_t i=0; i<=solucao.size()-1; i++){
		if(solucao[i]!=-1){
			double d = euclideanMetric(acessP, people, solucao[i], i);
			if(d>max_dist){max_dist=d;}
			mean_dist += d;
			contConect[solucao[i]]++;
		}else{notConect++;}
	}

	// Penalizar Não Conectados
	double penl_nConetado = 0.0;
	penl_nConetado += notConect * (max_dist+10);
	
	// Penalizar Violação Limite
	double penl_Limite = (3*max_dist) * aboveLimt(acessP, solucao);
	
	return (mean_dist+penl_nConetado+penl_Limite)/solucao.size();
}



double meanDist(vector<vector<float>> acessP, vector<vector<float>> people, vector<int> solucao){
	int cont=0;
	double dist = 0;
	for(size_t i=0; i<=solucao.size()-1; i++){
		dist += euclideanMetric(acessP, people, solucao[i], i);;
		cont++;
	}
	return dist/cont;
}

double sumDist(vector<vector<float>> acessP, vector<vector<float>> people, vector<int> solucao){
	double dist = 0;
	for(size_t i=0; i<=solucao.size()-1; i++){
		dist += euclideanMetric(acessP, people, solucao[i], i);;
	}
	return dist;
}

vector<int> acessPointDistribution(std::vector<std::vector<float>> acessP, std::vector<int> solucao){
	std::vector<int> contConect(acessP.size(), 0);
	for(size_t i=0; i<=solucao.size()-1; i++){
		if(solucao[i]!=-1){contConect[solucao[i]]++;}
	} return contConect;
}

int aboveLimt(vector<vector<float>> acessP, vector<int> solucao){
	std::vector<int> contConect(acessP.size(), 0);
	for(size_t i=0; i<=solucao.size()-1; i++){
		if(solucao[i]!=-1){contConect[solucao[i]]++;}
	}
	int lim;
	int sum=0;
	for(size_t i=0; i<=contConect.size()-1; i++){
		lim = (int)acessP[i][acessP[0].size()-1];
		sum += max(0, contConect[i] - lim);
	} return sum;
}


int nonConect(vector<int> solucao){
	int cont = 0;
	for(size_t i=0; i<=solucao.size()-1; i++){
		if(solucao[i]==-1){cont++;}
	}
	return cont;
}


