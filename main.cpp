#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <random>
#include "problema.h"
#include "EA.h"

using namespace std;

int popsize = 200;
int gensize = 5;
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
  ss << "EA_test_" << popsize << "_" << gensize << "_" << rounds << "_" << percent << "_" << elitism << ".txt";
  resultList.open(ss.str());

  while (getline(readlist,line))
  {
  stringstream ss;
  ss << "Benchmark/" << line;
      fileslist.push_back(ss.str());
  }

  readlist.close();
  ofstream results;
  results.open("EAresults.txt");

  for (int i = 0; i < fileslist.size(); i++)
  {
    int R;
    PolyFitP p(fileslist[i]);
    cout << "File: " << fileslist[i] << endl;

    EA algorithm(p, popsize, gensize);
    R = algorithm.runEA(p, rounds);

    cout << "mean fitness: " << algorithm.getMean() << ", best: " << algorithm.population[algorithm.getBest()].fitness << endl;

    resultList << fileslist[i] << "\t" << R << "\t" << algorithm.getMean() << "\t" << algorithm.population[algorithm.getBest()].fitness << "\t" << algorithm.stdev() << endl;

    results << fileslist[i] << "\t" << algorithm.population[algorithm.getBest()].disp() << endl;
    cout << endl << endl;
  }
  results.close();
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
  ss << "GA_test_" << popsize << "_" << gensize << "_" << rounds << "_" << percent << "_" << elitism << ".txt";
  resultList.open(ss.str());

  while (getline(readlist,line))
  {
  stringstream ss;
  ss << "Benchmark/" << line;
      fileslist.push_back(ss.str());
  }

  readlist.close();
  ofstream results;
  results.open("GAresults.txt");
  for (int i = 0; i < fileslist.size(); i++)
  {
    int R;
    PolyFitP p(fileslist[i]);
    cout << "File: " << fileslist[i] << endl;

    EA algorithm(p, popsize, gensize);
    R = algorithm.runGA(p, rounds, percent, true, elitism, false);

    cout << "mean fitness: " << algorithm.getMean() << ", best: " << algorithm.population[algorithm.getBest()].fitness << endl;

    resultList << fileslist[i] << "\t" << R << "\t" << algorithm.getMean() << "\t" << algorithm.population[algorithm.getBest()].fitness << "\t" << algorithm.stdev() << endl;

    results << fileslist[i] << "\t" << algorithm.population[algorithm.getBest()].disp() << endl;
    cout << endl << endl;
  }
  results.close();
  resultList.close();
}

void testHBDFunct ()
{
  ifstream readlist;
  ofstream resultList;
  vector<string> fileslist;
  string line;

  readlist.open("files.txt");
  stringstream ss;
  ss << "HBD_test_" << popsize << "_" << gensize << "_" << rounds << "_" << percent << "_" << elitism << ".txt";
  resultList.open(ss.str());

  while (getline(readlist,line))
  {
    stringstream ss;
    ss << "Benchmark/" << line;
    fileslist.push_back(ss.str());
  }

  readlist.close();
  ofstream results;
  results.open("HBDresults.txt");

  for (int i = 0; i < fileslist.size(); i++)
  {
    int R;
    PolyFitP p(fileslist[i]);
    cout << "File: " << fileslist[i] << endl;

    EA algorithm(p, popsize, gensize);
    R = algorithm.runGA(p, rounds, percent, true, elitism, true);

    cout << "mean fitness: " << algorithm.getMean() << ", best: " << algorithm.population[algorithm.getBest()].fitness << endl;

    resultList << fileslist[i] << "\t" << R << "\t" << algorithm.getMean() << "\t" << algorithm.population[algorithm.getBest()].fitness << "\t" << algorithm.stdev() << endl;

    results << fileslist[i] << "\t" << algorithm.population[algorithm.getBest()].disp() << endl;
    cout << endl << endl;
  }
  results.close();
  resultList.close();
}

int main(int argc, char* argv[])
{
    testGAFunct();
    testEAFunct();
    testHBDFunct();
    return 0;
}
