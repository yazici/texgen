#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

#include "random.h"

using namespace Tai;
using namespace std;

template <class Gene, class FitnessFunction>
GeneticAlgorithm<Gene,FitnessFunction>::GeneticAlgorithm(const FitnessFunction& ff) : fitnessFunction(ff)
{
}

template <class Gene, class FitnessFunction>
GeneticAlgorithm<Gene,FitnessFunction>::~GeneticAlgorithm()
{
}

template <class Gene, class FitnessFunction>
void GeneticAlgorithm<Gene,FitnessFunction>::iterate()
{

	// Selection for crossover
	// Mutation
	// Fitness Calculation
	// Selection of next generation
	
	int populationSize = population.size();
	//population.reserve(2*populationSize);

	for (int cnt = 0; cnt < populationSize; ++cnt)
	{
		int mate = int(randomd()*populationSize);
		while (mate == cnt && populationSize > 2)
		{
			mate = int(randomd()*populationSize);
		}

		Gene offspring;
		
		//if (randomd() > 0.5)
		//{
		//	offspring = Gene::crossOver(population[cnt], population[mate]);
		//}
		//else
		{
			offspring = population[cnt];
		}
		//Gene offspring(population[cnt]);// = Gene::crossOver(population[cnt], population[mate]);
		offspring.mutate(0.07, 0.01);
		//offspring.mutate(0.1, 0.5*(cnt + 1.0)/populationSize);
		fitnessFunction.calculate(offspring);
		if (offspring.fitness() < population[cnt].fitness())
		{
			population[cnt] = offspring;
		}
		//population.push_back(offspring);
	}


	/*typename vector<Gene>::iterator gene_it = population.begin();
	for (; gene_it != population.end(); ++gene_it)
	{
		fitnessFunction.calculate(*gene_it);
	}*/

	sort(population.begin(), population.end(), MoreFit());

	// kill of weaker part of population
	/*while (population.size() > populationSize)
	{
		population.pop_back();
	}*/
}

template<class Gene, class FitnessFunction>
void GeneticAlgorithm<Gene,FitnessFunction>::setInitialPopulation(const vector<Gene>& initialPopulation)
{
	population = initialPopulation;
	
	typename vector<Gene>::iterator gene_it = population.begin();
	for (; gene_it != population.end(); ++gene_it)
	{
		fitnessFunction.calculate(*gene_it);
	}

	sort(population.begin(), population.end(), MoreFit());
}
