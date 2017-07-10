#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <random>
#include "problema.h"
#include "GA.h"
#include "EA.h"

using namespace std;

int popsize = 200;
int gensize = 5;
int rounds = 100000;
int percent = 400;
bool elitism = false;

int main(int argc, char* argv[])
{
    ifstream readlist;
    ofstream resultList;
    vector<string> fileslist;
    string line;
    
    readlist.open("files.txt");
    resultList.open("EA_tests_200_5_100000.txt");
    
    while (getline(readlist,line))
    {
		stringstream ss;
		ss << "Benchmark/" << line;
        fileslist.push_back(ss.str());
    }
    
    readlist.close();
	
	for (int i = 0; i < fileslist.size(); i++)
	{
        int R;
		PolyFitP p(fileslist[i]);
		cout << "File: " << fileslist[i] << endl;
		
		EA algorithm(p, popsize, gensize);	
		R = algorithm.runEA(p, rounds);
		
		cout << "mean fitness: " << algorithm.getMean() << ", best: " << algorithm.population[algorithm.getBest()].fitness << endl;
        resultList << "Rounds:" << R << ", mean fitness: " << algorithm.getMean() << ", best: " << algorithm.population[algorithm.getBest()].fitness << endl;
		resultList << algorithm.population[algorithm.getBest()].disp() << endl;
		cout << endl << endl;
	}
	resultList.close();
    return 0;
}

