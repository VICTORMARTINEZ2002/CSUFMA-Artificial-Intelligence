#include <stdlib.h>

#include "../Metrics/Metrics.h"
#include "Individuo.cpp"

class Population{
public:
	std::vector<std::vector<float>> acessP;
	std::vector<std::vector<float>> people;
	std::vector<Individuo> indiv; // Vector to store individuals 
	int tamPop;                   // Size of the population
	int tamInd;                   // Size of each individual
	int qtdAcessP;                // Qtd pontos de acesso

	double sumFit;                // Sum of fitness of the population	
	int best;                     // Position of the best individual
	int pior;                     // Position of the worst individual
	int numMuta;                  // Number of mutations
	int iguais;                   // Count of reproductions with identical parents
	int bestGer;                  // Generation of the best individual


public:
	// Constructor
	Population(vector<vector<float>> acessP, vector<vector<float>> people, int maxPop){
		this->acessP    = acessP;
		this->people    = people;
		this->tamInd    = people.size();
		this->qtdAcessP = acessP.size();
		this->indiv     = std::vector<Individuo>(maxPop, Individuo(tamInd));

		this->sumFit  =  0;
		this->best    = -1;
		this->pior    = -1;
		this->numMuta =  0;
		this->iguais  =  0;
		this->bestGer = -1;	
		this->tamPop  = maxPop;
		
	}

	// Getters
	double getSumFit()const{ return sumFit;}
	int    getTamPop()const{ return tamPop;}
	int    getTamInd()const{ return tamInd;}
	int      getBest()const{   return best;}
	int      getPior()const{   return pior;}
	int   getNumMuta()const{return numMuta;}
	int    getIguais()const{ return iguais;}
	int   getBestGer()const{return bestGer;}
	Individuo& getIndiv(int index){return indiv.at(index);}

	// Setters
	void setSumFit(double value){   sumFit=value;}
	void      setBest(int value){     best=value;}
	void      setPior(int value){     pior=value;}
	void   setNumMuta(int value){  numMuta=value;}
	void    setIguais(int value){   iguais=value;}
	void   setBestGer(int value){  bestGer=value;}
	void setIndiv(int index, const Individuo& individuo){
		if((index>=0) && (index < tamPop)){this->indiv[index] = individuo;}
	}
  

	// Methods
	void initPopulacao(int flag){
		this->pior=0;
		this->best=0;
		this->sumFit=0;
		this->iguais=0;
		this->bestGer=1;
		this->numMuta=0;
		for(int i=0; i<=tamPop-1; i++){
			indiv[i].initIndividuo(this->acessP, this->people, flag);
			this->sumFit += indiv[i].getFit();
			if(indiv[i].getFit()>indiv[this->pior].getFit()){this->pior=i;}
			if(indiv[i].getFit()<indiv[this->best].getFit()){this->best=i;}
		}
		return;
	}

	void print(){
		cout << "Imprimindo a População\n";
		for(size_t i=0; i<=this->indiv.size()-1; i++){
			cout << "Indv " << i << ": ";
			this->indiv[i].print();
			this->indiv[i].printFit();
			this->indiv[i].printNoC();
			this->indiv[i].printAbL(acessP);
			cout << endl;
		}
	}

};
