#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

#include "../Metrics/Metrics.h"
#include "../Functions/auxFunc.h"


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
	int getVar(size_t index) const{
		if(index<var.size()){return var.at(index);}
		return -2;
	}
	const std::vector<int>& getVars() const{return var;}
	double getFit() const{return fit;}
	int    getOut() const{return out;}

	// Sets
	void setVars(const std::vector<int>& var){this->var=var;}
	void setFit(double fit){this->fit = fit;}
	void setOut(   int out){this->out = out;}
	void setVar(size_t index, int value){
		if(index<var.size()){var.at(index)=value;}
		else{printf("Error - setVar Individuo");}
	}

	// Methods
	void initIndividuo(vector<vector<float>> acessP, vector<vector<float>> people){
		for(size_t i=0; i<=var.size()-1; i++){
			var[i]=rand()%(acessP.size()+1);
			var[i]--; // Incluir o -1
		}
		this->fit = fitness(acessP, people, this->var);
		this->out = outs();
	}

	int outs(){
		int cont=0;
		for(size_t i=0; i<=var.size()-1; i++){
			if(var[i]==-1){cont++;}
		} return cont;
	}

	void resizeVars(int newSize, int defaultValue = 0){var.resize(newSize, defaultValue);}

	void    print(){for(int v : var){std::cout << v  << " ";}}
	void printFit(){std::cout <<   "\nFitness: " << fit;}
	void printNoC(){std::cout << "\nNo Connct: " << out;}
	void printAbL(vector<vector<float>> acessP){
		std::cout << "\nAbv Limit: " << aboveLimt(acessP, this->var);
	}

};
