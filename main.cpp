#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <random>
#include "problema.h"
#include "EA.h"

using namespace std;

int popsize = 20;
int gensize = 4;
int rounds = 1000000;
int percent = 400;
bool elitism = false;

void testEAFunct ()
{
  ifstream readlist;
  ofstream resultList;
  vector<string> fileslist;
  string line;

  readlist.open("files.txt");

  stringstream ss;
  ss << "EA_tests_" << popsize << "_" << gensize << "_" << rounds << "_" << percent << "_" << elitism << ".txt";
  resultList.open(ss.str());

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
}

void testGAFunct ()
{
  ifstream readlist;
  ofstream resultList;
  vector<string> fileslist;
  string line;

  readlist.open("files.txt");
  stringstream ss;
  ss << "GA_tests_" << popsize << "_" << gensize << "_" << rounds << "_" << percent << "_" << elitism << ".txt";
  resultList.open(ss.str());

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
    R = algorithm.runGA(p, rounds, percent, true, elitism);

    cout << "mean fitness: " << algorithm.getMean() << ", best: " << algorithm.population[algorithm.getBest()].fitness << endl;
        resultList << "Rounds:" << R << ", mean fitness: " << algorithm.getMean() << ", best: " << algorithm.population[algorithm.getBest()].fitness << endl;
    resultList << algorithm.population[algorithm.getBest()].disp() << endl;
    cout << endl << endl;
  }
  resultList.close();
}

int main(int argc, char* argv[])
{
    //testGAFunct();
    testEAFunct();
    return 0;
}
