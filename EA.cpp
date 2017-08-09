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

void EA::EVmutation(PolyFit * s, double sigma)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static default_random_engine gen(seed);
	normal_distribution<double> dist(0.0,sigma);

	for (int i = 0; i < gsize; i++)
	{
		s->solSpace[i] += dist(gen);
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

void EA::autoEvolve(PolyFitP prob, int round)
{
	for (int i = 0; i < size; i++)
	{
		PolyFit s(gsize);
		int p1 = i;
		s = population[p1];
        
        int seed = std::chrono::system_clock::now().time_since_epoch().count();
        static default_random_engine gen(seed);
        normal_distribution<double> dist(0.0,1.0);
		double sigma = 0.5*dist(gen);
		
        EVmutation(&s, sigma);
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
		autoEvolve(problem, i);
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

int EA::runGA(PolyFitP problem, int rounds, int percentage, bool compete, bool elitism, bool hybrid)
{
	int i = 0;
	int posbest = getBest();
	double mean = getMean();

	while (i < rounds && stdev() > 0.1)
	{
		reproduceAndSweep(percentage, problem, compete, elitism);
		if (hybrid)
        {
            for (int i = 0; i < 10; i++) autoEvolve(problem, i);
        }
        i++;
		posbest = getBest();
		mean = getMean();
		cout << "Round: " << i << " Mean: " << mean << " Best: " << population[posbest].fitness << " St. Dev.: " << stdev() << "            \r";
	}
	cout << endl;
    return i;
}

PolyFit EA::crossover(int pos1, int pos2)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static default_random_engine gen(seed);

	PolyFit ans(gsize);
	for (int i = 0; i < gsize; i++)
	{
		double x1, x2;
		x1 = population[pos1].solSpace[i];
		x2 = population[pos2].solSpace[i];
		normal_distribution<double> dist(0.0,1.0);
		ans.solSpace[i] = ((x1+x2)/2) + abs(x1-x2)*dist(gen);
	}
	return ans;
}

void EA::mutation(PolyFit * s, double mtax)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    uniform_real_distribution<double> distribution(0.0,1.0);
	static default_random_engine gen(seed);
	for (int i = 0; i < gsize; i++)
	{
		normal_distribution<double> dist(0.0,1.0);
		if (distribution(gen) > mtax) s->solSpace[i] += 0.05*dist(gen);
	}
}

void EA::reproduceAndSweep(int percent, PolyFitP prob, bool compete, bool elitism)
{
	int numberOfSons = (size*percent)/100;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static default_random_engine gen(seed);

	for (int i = 0; i < numberOfSons; i++)
	{
		PolyFit s(gsize);
		uniform_int_distribution<int> distribution(0,size-1);
		uniform_int_distribution<int> eld(0,2*size/3);
		int p1 = distribution(gen);
		int p2;

		if (elitism) p2 = eld(gen);
		else p2 = distribution(gen);

		s = crossover(p1,p2);
		mutation(&s, 0.1);
		s.getFitness(prob);
		population.push_back(s);
	}
	fitSort();
	//while (population.size() > size)
	{
		population.erase(population.end()-numberOfSons, population.end());
	}
}
