#include <vector>
#include <stdlib.h>
#include <time.h>

//#include "Classes/Population.cpp"

#define RAND_01 (static_cast<float>(rand()) / static_cast<float>(RAND_MAX))


#define FATOR 10
int Selecao(const Population& p){
	double val = 0.0;
	double spin_val = RAND_01 * p.sumFit;
	int i = rand()%p.tamPop;

	do{
		i = (i<p.tamPop-1) ? i+1 : 0;
		val += fabs(FATOR*p.sumFit) / (1 + p.indiv[i].fit - p.indiv[p.best].fit);
	}while(val<spin_val);

	return i;        // posição do estouro
}