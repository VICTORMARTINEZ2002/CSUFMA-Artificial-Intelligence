#include <vector>
#include <stdlib.h>
#include <time.h>

//#include "Classes/Population.cpp"

#define RAND_01 (static_cast<float>(rand()) / static_cast<float>(RAND_MAX))


#define FATOR .3
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

void CrossOver(Population& p, int pa1, int pa2){
	int corte = rand()%(p.tamInd);
    for(int i=0; i<p.tamInd; i++){
        if(i<corte){p.indiv[p.pior].var[i] = p.indiv[pa1].var[i];}
        else{       p.indiv[p.pior].var[i] = p.indiv[pa2].var[i];}
    }
}

#define PATUAL 10
void AtualizaPop(Population& p, int pos, double fit, int ger){
	// Atualiza Parametros
	p.sumFit += (fit - p.indiv[pos].fit);
	p.indiv[pos].fit = fit;
	p.indiv[pos].fixOut();

	// Verificar se novo melhor
	if(fit < p.indiv[p.best].fit){
		p.best = pos;
		p.bestGer=ger;
	}

	// Achar novo Pior
	int max = (PATUAL*p.tamPop)/100;
	for(int i=0; i<max-1; i++){
		int j = rand()%p.tamPop;
		if(j==pos || j==p.best){continue;}
		if(p.indiv[j].fit > p.indiv[p.pior].fit){
		  	p.pior = j;
			i += PATUAL;
		}
	}

}

void mutate(Population& p, int pos, int currGer, int maxGer){
	double frac=(currGer/maxGer);
	if(frac>.5 && currGer<25){
		for(int k=0; k<=(frac*FATOR*p.tamInd); k++){ 
			int i = rand()%(p.tamInd);
			int j = rand()%(p.tamInd);
			if(i!=j){
				int aux = p.indiv[pos].var[i];
				p.indiv[pos].var[i] = p.indiv[pos].var[j];
				p.indiv[pos].var[j] = aux;
			}
		}
	}else{for(int k=0; k<=(frac*FATOR*p.tamInd); k++) p.indiv[pos].var[rand()%(p.tamInd)] = rand()%p.acessP.size();}
}