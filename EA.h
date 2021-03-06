/**
Mateus Coelho Silva
DECOM - UFOP

Organizacao do Algoritmo Evolutivo
Busca por uma solucao para regressao linear multivariavel
para qualquer funcao

Baseada na organizacao sugerida pelo prof
Alan de Freitas
*/

#ifndef __EA__
#define __EA__

#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include "problema.h"
#include "solucao.h"

using namespace std;

class EA
{
public:
	//composes the population
	vector<PolyFit> population;

	//constructor for a EA
	EA(PolyFitP prob, int popsize = 50, int genSize = 3);

	///Functions
	//runs EA for a number of iterations or a criteria
	int runEA(PolyFitP problem, int rounds = 10000);
    //runs GA for a number of iterations or a criteria
	int runGA(PolyFitP problem, int rounds = 10000, int percentage = 10, bool compete = true, bool elitism = false, bool hybrid = true);
    
	//display population
	void disp();
    //crossover function
	PolyFit crossover(int pos1, int pos2);
	//mutation function
	void mutation(PolyFit * s, double sigma);
    //Auto evolution mutation
    void EVmutation(PolyFit * s, double sigma);

	//standard deviation for stop point
	double stdev();
	//finds standard deviation for a problem's fitness vector
	double getMean();
	//gets best solution from a solspace
	int getBest();

private:
	//extra information	
	int size;
	int gsize;

	///functions
	//sorts population according to fitness
	void fitSort();
	//reproduces than selects with tournament
	void reproduceAndSweep(int percent, PolyFitP prob, bool compete, bool elitism);
    //Auto evolve
    void autoEvolve(PolyFitP prob, int round);
    
};

#endif
