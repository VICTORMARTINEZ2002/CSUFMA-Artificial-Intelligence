#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Leitura/read.h"
#include "Metrics/metrics.h"
#include "Classes/Population.cpp"
#include "Functions/auxFunc.h"
#include "bestFit.cpp"
//#include "geneticAlgorithm.cpp"

#define PEOPLE_PATH "Data/people.csv"
#define ACESSP_PATH "Data/acessPoint.csv"

#define MAXPOP 100

using namespace std;

int main(){
    vector<vector<float>> people;
    readCSV(PEOPLE_PATH, people);
    vector<vector<float>> acessP; // Lembrar de cast (int) Limite
    readCSV(ACESSP_PATH, acessP);

    vector<int> s(people.size(), -1);
    bestFit(s, people, acessP);
    for(size_t i=0; i<=s.size()-1; i++){
        cout << s[i] << " ";
    }
    printf("Fitness = %lf\n", fitness(acessP,people,s));
    printf("Dist M  = %lf\n", meanDist(acessP,people,s));
    printf("nonConect  = %d\n", nonConect(s));
    vector<int> apd = acessPointDistribution(acessP,s);
    for(size_t i=0; i<=apd.size()-1; i++){
        cout << apd[i] << " ";
    } cout << endl;
    printf("aboveLimt  = %d\n", aboveLimt(acessP,s));
    

    Population p(acessP, people, MAXPOP);
    p.initPopulacao();
    p.print();
    // erro = (double) P.indiv[P.melhor].fit - SOLUCAO;

    // clock_t start = clock();
    // while((numGeracoes>=0) && (Aval<MAXAVA) && (erro>(double)0.0F)){
    //     numCruza = NUMCRU;
    //     while(numCruza --){
    //         pa1=Selecao(&P);
    //         pa2=Selecao(&P);
    //         if(pa1!=pa2){CruzaBlend(&P, pa1, pa2, P.pior, XALFA);}else{P.iguais++;}
    //         if(PMUTAC > rand()%100){
    //             nu_mutate(P.indiv[P.pior].var, P.tamInd, P.tamPop, MAXGER - numGeracoes, MNUNI);
    //             P.numMuta ++;
    //         }
    //         fit = funccod[FUNCAO](P.indiv[P.pior].var, P.tamInd);
    //         if(fit < P.indiv[P.melhor].fit){
    //             addBuffer++;
    //             addToBuffer(buffer, P.indiv[P.melhor].var);
    //         }
    //         AtualizaPop(&P, P.pior, fit, MAXGER - numGeracoes);
    //     }
    //     erro = (double) P.indiv[P.melhor].fit - SOLUCAO;

    //     numGeracoes--;

    // }

    // clock_t end = clock();

    for(size_t i=0; i<=acessP.size()-1; i++){
        for(size_t j=0; j<=acessP[i].size()-1; j++){
            cout << acessP[i][j] << " ";
        }
        cout << endl;
    }


    // for(size_t i=0; i<=people.size()-1; i++){
    //     for(size_t j=0; j<=people[i].size()-1; j++){
    //         cout << people[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    printf("Fim do Programa.");
    return 0;
}