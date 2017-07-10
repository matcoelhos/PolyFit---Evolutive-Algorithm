#include "solucao.h"

using namespace std;

PolyFit::PolyFit(int ns)
{
    nsize = ns;
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    uniform_real_distribution<double> distribution(-10.0,10.0);
    static default_random_engine generator(seed);
 
	for (int j = 1; j <= nsize; j++)
	{
		double factor = 1;
	    double el = distribution(generator);
	    solSpace.push_back((el*factor));
	}
	
}

string PolyFit::disp()
{
    stringstream ss;
    for (int i = 0; i < solSpace.size(); i++)
    {
		cout << solSpace[i] << " ";
        ss << solSpace[i] << " ";
	}
    return ss.str();
	cout << endl;
}

void PolyFit::getFitness(PolyFitP P)
{
	double ISE = 0;
	double sum = 0;
	for (int i = 0; i < P.pairs.size(); i++)
	{
		double yhat = 0;
		for (int j = 0; j < nsize; j++)
		{
			yhat += ((solSpace[j] * pow(P.pairs[i][0], (nsize - j - 1))));
		}
		ISE += ((yhat - P.pairs[i][1])*(yhat - P.pairs[i][1]));
		//sum += abs(P.pairs[i][0]);
	}
	fitness = ISE/P.pairs.size();
}



