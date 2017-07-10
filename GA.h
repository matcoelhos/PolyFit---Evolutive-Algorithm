/**
Mateus Coelho Silva
DECOM - UFOP

Organizacao do Algoritmo G
Busca por uma solucao para regressao linear multivariavel
para qualquer funcao

Baseada na organizacao sugerida pelo prof
Alan de Freitas
*/

#ifndef __GA__
#define __GA__

#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include "problema.h"
#include "solucao.h"

using namespace std;

class GA
{
public:
	//composes the population
	vector<PolyFit> population;

	//constructor for a GA
	GA(PolyFitP prob, int popsize = 50, int genSize = 3);

	///Functions
	//runs GA for a number of iterations or a criteria
	int runGA(PolyFitP problem, int rounds = 10000, int percentage = 10, bool compete = true, bool elitism = false);
	//display population
	void disp();
	//crossover function
	PolyFit crossover(int pos1, int pos2);
	//mutation function
	void mutation(PolyFit * s, double mtax);

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

};

#endif
