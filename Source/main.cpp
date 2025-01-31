#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

#include "Leitura/read.h"
#include "Metrics/metrics.h"
#include "Classes/Population.cpp"
#include "Functions/auxFunc.h"

#include "bestFit.cpp"
#include "geneticAlgorithm.cpp"

#define PEOPLE_PATH "Data/people.csv"
#define ACESSP_PATH "Data/acessPoint.csv"

#define MAXPOP 100
#define MAXGER 50
#define NUMCRU 85
#define PMUTAC 20

using namespace std;

int main(){
	vector<vector<float>> people;
	readCSV(PEOPLE_PATH, people);
	vector<vector<float>> acessP; // Lembrar de cast (int) Limite
	readCSV(ACESSP_PATH, acessP);


	// for(size_t i=0; i<=acessP.size()-1; i++){
	//     for(size_t j=0; j<=acessP[i].size()-1; j++){
	//         cout << acessP[i][j] << " ";
	//     }
	//     cout << endl;
	// }


	// for(size_t i=0; i<=people.size()-1; i++){
	//     for(size_t j=0; j<=people[i].size()-1; j++){
	//         cout << people[i][j] << " ";
	//     }
	//     cout << endl;
	// }

	vector<int> s(people.size(), -1);
	Individuo best = bestFit(s, people, acessP);
	for(size_t i=0; i<=s.size()-1; i++){
		cout << best.var[i] << " ";
	} printStatusSolution(acessP, people, best.var);
	
	
	

	Population p(acessP, people, MAXPOP);
	p.initPopulacao();
	//p.print();
	
	

	int currGer=0;
	double erro = (double) p.indiv[p.best].fit - best.fit;

	clock_t start = clock();
	while((currGer<MAXGER) && (erro>(double)1.0)){
		int numCruza = NUMCRU;
		while(numCruza--){
			int pa1 = Selecao(p);
			int pa2 = Selecao(p);
			if(pa1!=pa2){CrossOver(p, pa1, pa2);}else{p.iguais++;}
			if(PMUTAC > rand()%100){
				mutate(p, p.pior);
				p.numMuta ++;
			}
			double fit = fitness(acessP, people, p.indiv[p.pior].var);
			AtualizaPop(p, p.pior, fit, currGer);
		}
		erro = (double) p.indiv[p.best].fit - best.fit;
		printf("Erro da Geração %d: %.2lf\n", currGer, erro);
		currGer++;
	}
	clock_t end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC;

	cout << "Melhor Solução: ";
	// for(size_t i=0; i<=s.size()-1; i++){
	// 	cout << p.indiv[p.best].var[i] << " ";
	// } 
	printStatusSolution(acessP, people, p.indiv[p.best].var);

	printf("Tempo do AG: %lf\n", time);
	printf("Fim do Programa.\n\n\n");
	return 0;
}