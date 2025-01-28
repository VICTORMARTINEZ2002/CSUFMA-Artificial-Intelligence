#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "readCsv.cpp"
#include "bestFit.cpp"
//#include "geneticAlgorithm.cpp"

#define PEOPLE_PATH "../Data/people.csv"
#define ACESSP_PATH "../Data/acessPoint.csv"

#define MAXPOP 100

using namespace std;

int main(){
    vector<vector<float>> people;
    readCSV(PEOPLE_PATH, people);
    vector<vector<float>> acessP;
    readCSV(ACESSP_PATH, acessP);

    vector<int> s(people.size(), -1);
    bestFit(s, people, acessP);
    for(int i=0; i<=s.size()-1; i++){
        cout << s[i] << " ";
    }
    printf("Dist M = %lf\n", fitness(acessP,people,s));
    
    População P;
    IniciaPop(&P, MAXPOP, people);
    erro = (double) P.indiv[P.melhor].fit - SOLUCAO;

    clock_t start = clock();
    while((numGeracoes>=0) && (Aval<MAXAVA) && (erro>(double)0.0F)){
        numCruza = NUMCRU;
        while(numCruza --){
            pa1=Selecao(&P);
            pa2=Selecao(&P);
            if(pa1!=pa2){CruzaBlend(&P, pa1, pa2, P.pior, XALFA);}else{P.iguais++;}
            if(PMUTAC > rand()%100){
                nu_mutate(P.indiv[P.pior].var, P.tamInd, P.tamPop, MAXGER - numGeracoes, MNUNI);
                P.numMuta ++;
            }
            fit = funccod[FUNCAO](P.indiv[P.pior].var, P.tamInd);
            if(fit < P.indiv[P.melhor].fit){
                addBuffer++;
                addToBuffer(buffer, P.indiv[P.melhor].var);
            }
            AtualizaPop(&P, P.pior, fit, MAXGER - numGeracoes);
        }
        erro = (double) P.indiv[P.melhor].fit - SOLUCAO;

        
        if(flag_teste && mustSendBuffer(buffer, MAXGER-numGeracoes)){
            flag_teste = false;
            MPI_Send(buffer, 1, bufferTypeMPI, RANK_GPILHA, TAG_MESTRE, MPI_COMM_WORLD);
            //emptyBuffer(buffer);
            printf("Enviei");
        }
        numGeracoes--;

    }

    clock_t end = clock();

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

    printf("Fim do Programa.");
    return 0;
}