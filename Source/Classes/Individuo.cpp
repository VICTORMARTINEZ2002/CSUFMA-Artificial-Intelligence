#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double dist(vector<vector<float>> acessP, vector<vector<float>> people, int a, int p){
	double dist=0;
	int dim = acessP[0].size()-1;
	for(int i=0; i<=dim-1; i++){
		if(a==-1){dist+=5000; continue;}
		dist += pow(acessP[a][i]-people[p][i], 2);
	}
	return sqrt(dist);
}

double fitness(vector<vector<float>> acessP, vector<vector<float>> people, vector<int> solucao){
	int notConect=0;
	double  max_dist = 0;
	double mean_dist = 0;
	std::vector<int> contConect(acessP.size()-1, 0);

	// Calculo Mean Distancias
	for(int i=0; i<=solucao.size()-1; i++){
		if(solucao[i]!=-1){
			double d = dist(acessP, people, solucao[i], i);
			if(d>max_dist){max_dist=d;}
			mean_dist += d;
			contConect[solucao[i]]++;
		}else{notConect++;}
	}

	// Penalizar Não Conectados
	double penl_nConetado = 0.0;
	penl_nConetado += notConect * (max_dist+10);
	
	// Penalizar Violação Limite
	double penl_Limite = 0;
	for(int i=0; i<=contConect.size()-1; i++){
		if(contConect[i]>acessP[i][acessP.size()-1]){
			penl_Limite += (contConect[i]-acessP[i][acessP.size()-1])*(3*max_dist);
		}
	}

	return (mean_dist+penl_nConetado+penl_Limite)/solucao.size();
}


class Individuo{
private:
	std::vector<int> var;
	double fit = 0.0;
	int out    = 0;

public:
	// Construtor
	Individuo(int numVars){
		this->var = std::vector<int>(numVars);
		this->fit = -1;
		this->out =  0;
	}

	// Gets
	int getVar(int index) const{
		if((index>=0) && (index<var.size())){return var.at(index);}
		return -2;
	}
	const std::vector<int>& getVars() const{return var;}
	double getFit() const{return fit;}
	int    getOut() const{return out;}

	// Sets
	void setVars(const std::vector<int>& var){this->var=var;}
	void setFit(double fit){this->fit = fit;}
	void setOut(   int out){this->out = out;}
	void setVar(int index, int value){
		if((index>=0) && (index<var.size())){var.at(index)=value;}
		else{printf("Error - setVar Individuo");}
	}

	// Methods
	void initIndividuo(vector<vector<float>> acessP, vector<vector<float>> people){
		srand(time(NULL));
		for(int i=0; i<=var.size()-1; i++){var[i]=rand()%(acessP.size()-1);}
		this->fit = fitness(acessP, people, this->var);
		this->out = outs();
	}

	int outs(){
		int cont=0;
		for(int i=0; i<=var.size()-1; i++){
			if(var[i]==-1){cont++;}
		} return cont;
	}

	void resizeVars(int newSize, int defaultValue = 0){var.resize(newSize, defaultValue);}

	void print() const{
		std::cout << "Variables: ";
		for(int v : var){std::cout << v << " ";}
		std::cout << "\nFitness: " << fit << "\nNon Connected: " << out << "\n";
	}
};
