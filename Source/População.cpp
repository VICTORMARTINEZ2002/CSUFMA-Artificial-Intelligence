class Populacao{
private:
	std::vector<Individuo> indiv; // Vector to store individuals
	double sumFit;                 // Sum of fitness of the population
	int tamPop;                    // Size of the population
	int tamInd;                    // Size of each individual
	int melhor;                    // Position of the best individual
	int pior;                      // Position of the worst individual
	int numMuta;                   // Number of mutations
	int iguais;                    // Count of reproductions with identical parents
	int gerMelhor;                 // Generation of the best individual

public:
	// Constructor
	Populacao(int maxPop, int tamInd, int acessP){
		this->individuo = std::vector<Individuo>,
		this->sumFit    =  0;
		this->melhor    = -1;
		this->pior      = -1;
		this->numMuta   =  0;
		this->iguais    =  0;
		this->gerMelhor = -1;	
		this->tamPop = maxPop;
		this->tamInd = tamInd;
		this->acessP = acessP; 
	}

	// Getters
	double getSumFit()const{return sumFit;}
	int    getTamPop()const{return tamPop;}
	int    getTamInd()const{return tamInd;}
	int    getMelhor()const{return melhor;}
	int      getPior()const{return pior;}
	int   getNumMuta()const{return numMuta;}
	int    getIguais()const{return iguais;}
	int getGerMelhor()const{return gerMelhor;}
	Cromossomo& getIndiv(int index){return indiv.at(index);}

	// Setters
	void setSumFit(double value){   sumFit=value;}
	void    setMelhor(int value){   melhor=value;}
	void      setPior(int value){     pior=value;}
	void   setNumMuta(int value){  numMuta=value;}
	void    setIguais(int value){   iguais=value;}
	void setGerMelhor(int value){gerMelhor=value;}
	void setIndiv(int index, const Cromossomo& cromossomo){
		if((index>=0) && (index < tamPop)){
			indiv[index] = cromossomo;
		}
	}

	// Methods
	initPopulacao(){
		for(int i=0; i<=tamPop-1; i++){
			int pior=0, melhor=0;
			double soma=0;
			double fit;
			individuo[i].initIndividuo(this->acessP);
		}
	}

};
