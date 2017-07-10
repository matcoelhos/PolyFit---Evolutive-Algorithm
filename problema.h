/**
    Mateus Coelho Silva
	DECOM - UFOP
    
    Instancia do problema
    Busca por uma solucao para regressao linear multivariavel
    para qualquer funcao

	Baseada na organizacao sugerida pelo prof
    Alan de Freitas  
*/

#ifndef __PolyFitP__
#define __PolyFitP__

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <random>

using namespace std;

/// This is a class that represents an instance of the polyfit problem
class PolyFitP
{
public:
    /// Creating a random problem of a given size
    PolyFitP(string file);

	//Vector to store the pairs of points from the generated function
	vector<vector<double>> pairs;

    // Non-modifying functions needed by the Genetic Algorithm
    /// Displays (prints) the problem instance
    void disp();

private:

    // Auxiliar variables which are important to generate random numbers
    static default_random_engine generator;

}; // fim da classe

#endif /* defined(__PolyFitP__) */
