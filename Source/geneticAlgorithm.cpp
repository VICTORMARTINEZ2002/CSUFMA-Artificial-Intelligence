#include <vector>
#include <stdlib.h>
#include <time.h>



#define xc 0
#define yc 1




extern void IniciaPop(Populacao *p, int popSize, int qtdPessoas){
	int pior=0, melhor=0;
	double soma=0;
	double fit;

	for(size_t i=0; i<=popSize-1; i++){
		for(size_t j=0; j<=qtdPessoas-1; j++){
			p->indiv[i].var[j] = (int)rand()%2;
		}
		fit = funccod[nfun](p->indiv[i].var, n);
		p->indiv[i].fit=fit;
		if (fit > p->indiv[pior].fit) pior = i;
		if (fit < p->indiv[melhor].fit) melhor = i;
		soma += (fit); //fabs
	}

	p->tamPop  = m;
	p->tamInd  = n;
	p->sumFit  = soma;
	p->pior    = pior;
	p->melhor  = melhor;
	p->numMuta = 0;
	p->iguais  = 0;
}

#include <iostream>
// int main(void){
// 	double d = dist(0, 1, 1);
// 	printf("%lf", d);
// }