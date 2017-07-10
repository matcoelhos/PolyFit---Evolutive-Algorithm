/**
	Mateus Coelho Silva
	DECOM - UFOP
    
    Solucao do problema
    Busca por uma solucao para regressao linear multivariavel
    para qualquer funcao

    Baseada na organizacao sugerida pelo prof
    Alan de Freitas   
*/

#ifndef __PolyFit__
#define __PolyFit__

#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <chrono>
#include "problema.h"

using namespace std;

/// This is a class that represents a solution space for the polyfit problem
class PolyFit
{
public:
    
	PolyFit(int ns);
    
	/// Container with the population
	vector<double> solSpace;
	//solution fitness
	double fitness;
	
	//display solution
    string disp();

    // Functions needed by the Genetic Algorithm
    
    /// Functions
    // Evaluates the solution and return the objective value
    // criteria: Integral square error.
	void getFitness(PolyFitP P);

 
private:    
    ///size of each solution;
    int nsize;

    ///Functions
};

#endif /* defined(__Matrizes__PolyFit__) */
