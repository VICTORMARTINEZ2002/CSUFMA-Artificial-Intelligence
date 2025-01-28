#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

#define MAXDOUBLE std::numeric_limits<double>::max()

using namespace std;

double dist(vector<vector<float>> acessP, vector<vector<float>> people, int a, int p){
	double dist=0;
	int dim = acessP[0].size()-1;
	for(int i=0; i<=dim-1; i++){
		dist += pow(acessP[a][i]-people[p][i], 2);
	}
	return sqrt(dist);
}

void bestFit(vector<int>& s, vector<vector<float>> people, vector<vector<float>> acessP){
	int QTD_PESSOAS = people.size();
	int QTD_ACESSOP = acessP.size();
	int LIMACSP = acessP[0].size()-1;

	//	vector<int> s(people.size(), -1); // Solução
	vector<int> c(QTD_ACESSOP,  0); // Contador de Conecções

	int maxCap=0;
	for(int i=0; i<=QTD_ACESSOP-1; i++){maxCap+= acessP[i][LIMACSP];}
	int connect = min(static_cast<int>(people.size()), maxCap);

	vector<vector<float>> distances(QTD_PESSOAS, vector<float>(QTD_ACESSOP));
	for(int i=0; i<=QTD_PESSOAS-1; i++){
		for(int j=0; j<=QTD_ACESSOP-1; j++){
			distances[i][j] = dist(acessP, people, j, i);
		}
	}

	// Melhoria: Considerar como vetor e ordenar com nlogn;
	for(int k=0; k<=connect-1; k++){
		double menor_dist = MAXDOUBLE;
		int menorp=0;
		int menorw=0;
		for(int i=0; i<=QTD_PESSOAS-1; i++){
			for(int j=0; j<=QTD_ACESSOP-1; j++){
				if(distances[i][j]<menor_dist){
					if((s[i]==-1) && (c[j]<acessP[j][LIMACSP])){
						menor_dist = distances[i][j];
						menorp = i;
						menorw = j;								
					}
				}
			}	
		}
		c[menorw]++;
		distances[menorp][menorw]=MAXDOUBLE;
		s[menorp]=menorw;
	}
	
}