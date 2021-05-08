#include <iostream>  
#include <math.h>                                     
#include <vector>                    
#include <algorithm>                 
#include <array>
#include "GeneticAlg.h"

GeneticAlg::GeneticAlg(int r, int g, int b)
{
	TargetColor[0] = r;
	TargetColor[1] = g;
	TargetColor[2] = b;
}

//Генерация начальной популяции
void GeneticAlg::GeneratePopulation(std::vector<Member>& population, std::vector<Member>& buffer)
{
	int tsize = 3;

	for (size_t i = 0; i < PopulationSize; i++)
	{
		Member citizen;

		citizen.fitness = 0;

		for (int j = 0; j < tsize; j++)
			citizen.color[j] = (rand() % MaxValue);

		population.push_back(citizen);
	}

	buffer.resize(PopulationSize);
}

//Вычисление приспособленности для популяции
void GeneticAlg::CalculateFitness(std::vector<Member>& population)
{
	std::array<int, 3> target = TargetColor;
	size_t tsize = target.size();
	unsigned int fitness;

	for (size_t i = 0; i < PopulationSize; i++) 
	{
		fitness = 0;
		for (size_t j = 0; j < tsize; j++) 
		{
			fitness += abs(int(population[i].color[j] - target[j])); //-V127
		}

		population[i].fitness = fitness;
	}
}

//сортировка по приспособленности 
inline void GeneticAlg::SortByFitness(std::vector<Member>& population)
{
	std::sort(population.begin(), population.end(), [&](auto x, auto y) { return (x.fitness < y.fitness); });
}
//Выделение элитных особей
void GeneticAlg::GetEletism(std::vector<Member>& population, std::vector<Member>& buffer, size_t esize)
{
	for (size_t i = 0; i < esize; i++) {
		buffer[i].color = population[i].color;
		buffer[i].fitness = population[i].fitness;
	}
}
//Мутация элемента 
void GeneticAlg::MutateMember(Member& member)
{
	int targetSize = TargetColor.size();
	int delta = (rand() % MaxValue);
	int position = rand() % targetSize;

	member.color[position] = ((member.color[position] + delta) % MaxValue);
}
//Скрещивание
void GeneticAlg::Crossover(std::vector<Member>& population, std::vector<Member>& buffer)
{
	size_t eletismSize = PopulationSize * ElitismRate;
	size_t targetSize = TargetColor.size(), spos, i1, i2;

	GetEletism(population, buffer, eletismSize);

	for (size_t i = eletismSize; i < PopulationSize; i++)
	{
		i1 = rand() % (PopulationSize / 2);
		i2 = rand() % (PopulationSize / 2);
		spos = rand() % targetSize;
		for (size_t j = 0; j < TargetColor.size(); j++)
		{
			int leftPart = (population[i1].color[j] & ((int)pow(2, 8) - (int)pow(2, spos))); //-V113
			int rightPart = (population[i2].color[j] & ((int)pow(2, spos) - 1)); //-V113
			buffer[i].color[j] = leftPart | rightPart;
		}

		if (rand() < Mutation)
			MutateMember(buffer[i]);
	}
}
//Вывод наиболее приспособленного элемента (для наглядности)
void GeneticAlg::PrintBest(std::vector<Member>& gav)
{
	std::cout << "Лучший в популяции: " << gav[0].color[0] << ", " << gav[0].color[1] << ", " << gav[0].color[2] << " (" << gav[0].fitness << ")" << std::endl;
}

inline void GeneticAlg::SwapBuffers(std::vector<Member>*& population,
	std::vector<Member>*& buffer)
{
	std::vector<Member>* temp = population; 
	population = buffer; 
	buffer = temp;
}

void GeneticAlg::RunAlgorithm()
{

	std::vector<Member> populationAlpha, populationBeta;
	std::vector<Member>* population, * buffer;

	GeneratePopulation(populationAlpha, populationBeta);
	population = &populationAlpha;
	buffer = &populationBeta;

	for (size_t i = 0; i < MaxIter; i++)
	{
		CalculateFitness(*population);       
		SortByFitness(*population);      
		PrintBest(*population);       

		if ((*population)[0].fitness == 0) 
			break;

		Crossover(*population, *buffer);        
		SwapBuffers(population, buffer);        
	}
}