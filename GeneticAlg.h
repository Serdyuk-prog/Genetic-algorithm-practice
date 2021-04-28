#include <vector>                    
               
#include <array>

struct Member
{
	std::array<int, 3> color;
	unsigned int fitness;
};


class GeneticAlg
{
private:
	const int MaxValue = 255;
	const size_t PopulationSize = 2048;
	const size_t MaxIter = 16384;
	const float ElitismRate = 0.10f;
	const float MutationRate = 0.25f;
	const float Mutation = RAND_MAX * MutationRate;

	//Генерация начальной популяции
	void GeneratePopulation(std::vector<Member>& population, std::vector<Member>& buffer);
	//Вычисление приспособленности для популяции
	void CalculateFitness(std::vector<Member>& population);
	//Сортировка по приспособленности 
	inline void SortByFitness(std::vector<Member>& population);
	//Выделение элитных особей
	void GetEletism(std::vector<Member>& population, std::vector<Member>& buffer, size_t esize);
	//Мутация элемента 
	void MutateMember(Member& member);
	//Скрещивание
	void Crossover(std::vector<Member>& population, std::vector<Member>& buffer);
	//Вывод наиболее приспособленного элемента (для наглядности)
	void PrintBest(std::vector<Member>& gav);
	inline void SwapBuffers(std::vector<Member>*& population, std::vector<Member>*& buffer);

public:
	GeneticAlg(int r, int g, int b);
	std::array<int, 3> TargetColor;
	void RunAlgorithm();
};