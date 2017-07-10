#include "EA.h"

using namespace std;

EA::EA(PolyFitP prob, int popSize, int genSize)
{
	size = popSize;
	gsize = genSize;
	for (int i = 0; i < popSize; i++)
	{
		PolyFit s(genSize);
		s.getFitness(prob);
		population.push_back(s);
	}
	fitSort();
}

void EA::disp()
{
	for (int i = 0; i < size; i++)
	{
		population[i].disp();
		cout << "fitness: " << population[i].fitness << endl;
	}
}

void EA::mutation(PolyFit * s, double sigma)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    	static default_random_engine gen(seed);
	normal_distribution<double> dist(0.0,1.0);	
	
	for (int i = 0; i < gsize; i++)
	{
		s->solSpace[i] += sigma*dist(gen);
	}
}

bool comp2 (PolyFit s1, PolyFit s2)
{
	return (s1.fitness < s2.fitness);
}

void EA::fitSort()
{
	sort(population.begin(), population.end(), comp2);
}

void EA::reproduceAndSweep(PolyFitP prob, int round)
{
	for (int i = 0; i < size; i++)
	{
		PolyFit s(gsize);
		int p1 = i;
		s = population[p1];

		double sigma = 0.05;
		mutation(&s, sigma);
		s.getFitness(prob);

		if (s.fitness < population[p1].fitness)
		{
			population.erase(population.begin() + p1);
			population.push_back(s);
		}
	}
}

int EA::runEA(PolyFitP problem, int rounds)
{
	int i = 0;
	int posbest = getBest();
	double mean = getMean();

	while (i < rounds && stdev() > 0.1)
	{
		reproduceAndSweep(problem, i);
		i++;
		posbest = getBest();
		mean = getMean();
		cout << "Round: " << i << " Mean: " << mean << " Best: " << population[posbest].fitness << " St. Dev.: " << stdev() << "            \r";
	}
	cout << endl;
        return i;
}

int EA::getBest()
{
	int pos = 0;
	double bestF = population[0].fitness;
	for (int i = 1; i < size; i++)
	{
		if (population[i].fitness < bestF)
		{
			bestF = population[i].fitness;
			pos = i;
		}
	}
	return pos;
}

double EA::getMean()
{
	double sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += population[i].fitness;
	}
	sum /= size;
	return sum;
}

double EA::stdev()
{
	double mean = getMean(), sum = 0;
	int N = population.size();

	for (int i = 0; i < N; i++)
	{
		sum += ((population[i].fitness - mean)*(population[i].fitness - mean));
	}
	sum /= N;
	return sqrt(sum);
}
