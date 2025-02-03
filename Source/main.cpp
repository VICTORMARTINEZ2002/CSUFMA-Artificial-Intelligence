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
#define MAXGER 10
#define NUMCRU 75
#define PMUTAC 85

#define FVAZIO 0
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
	p.initPopulacao(FVAZIO);
	//p.print();
	
	

	int currGer=0;
	double erro = (double) p.indiv[p.best].fit - best.fit;

	clock_t start = clock();
	while((currGer<MAXGER) && (erro>(double)0.0)){
		int numCruza = NUMCRU;
		while(numCruza--){
			int pa1 = Selecao(p);
			int pa2 = Selecao(p);
			if(pa1!=pa2){CrossOver(p, pa1, pa2);}else{p.iguais++;}
			if(PMUTAC > rand()%100){
				mutate(p, p.pior, currGer, MAXGER);
				p.numMuta ++;
			}
			double fit = fitness(acessP, people, p.indiv[p.pior].var);
			AtualizaPop(p, p.pior, fit, currGer);
		}
		erro = (double) p.indiv[p.best].fit - best.fit;
		//printStatusSolution(acessP, people, p.indiv[p.best].var);
		printf("Best Fitness Difference of GER %d Compared to Heuristic Approach: %.2lf\n", currGer, erro);
		currGer++;
	}
	clock_t end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC;

	cout << "Best Solution Finded: ";
	for(size_t i=0; i<=s.size()-1; i++){
		cout << p.indiv[p.best].var[i] << " ";
	} 
	printStatusSolution(acessP, people, p.indiv[p.best].var);

	printf("Tempo do AG: %lf\n", time);
	printf("Fim do Programa.\n\n\n");


	// Ploting the value with gnuplot
	std::ofstream dataFile("output.txt");
	if(!dataFile){std::cerr << "Unable to open data file!" << std::endl; return 1;}
	for(size_t i=0; i<=acessP.size()-1; i++){
		dataFile << i << " "
				  << acessP[i][0] << " "
				  << acessP[i][1] << " "
				  << -1 << std::endl; //black
	}
	for(size_t i=0; i<=s.size()-1; i++){
		dataFile << i+acessP.size()-1 << " "
				  << people[i][0]     << " "
				  << people[i][1]     << " "
				  << p.indiv[p.best].var[i] << std::endl;
	} dataFile.close();

	std::ofstream gnuplotScript("plot_script.gp");
	if(!gnuplotScript){std::cerr << "Unable to create gnuplot script!" << std::endl;return 1;}

	// Gnuplot commands to the script file
	gnuplotScript << "set terminal pdfcairo size 10, 8\n"; 
	gnuplotScript << "set output 'plot_output.pdf'\n";
	gnuplotScript << "set pointsize 1.5\n";
	gnuplotScript << "set palette defined (-1 'black', 0 'red', 1 'blue', 2 'green', 3 'yellow')\n"; // Define color palette
	gnuplotScript << "plot 'output.txt' using 2:3:4 with points pt 7 palette title '" << "Fitness = " << fitness(acessP, people, p.indiv[p.best].var)  << "'\n";
	gnuplotScript << "pause -1\n";
	gnuplotScript.close();

	std::system("gnuplot -persist plot_script.gp");
	std::remove("output.txt");
    std::remove("plot_script.gp");


	return 0;

	// Tempo

}