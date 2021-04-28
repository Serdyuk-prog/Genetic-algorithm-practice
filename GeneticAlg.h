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

	//��������� ��������� ���������
	void GeneratePopulation(std::vector<Member>& population, std::vector<Member>& buffer);
	//���������� ����������������� ��� ���������
	void CalculateFitness(std::vector<Member>& population);
	//���������� �� ����������������� 
	inline void SortByFitness(std::vector<Member>& population);
	//��������� ������� ������
	void GetEletism(std::vector<Member>& population, std::vector<Member>& buffer, size_t esize);
	//������� �������� 
	void MutateMember(Member& member);
	//�����������
	void Crossover(std::vector<Member>& population, std::vector<Member>& buffer);
	//����� �������� ���������������� �������� (��� �����������)
	void PrintBest(std::vector<Member>& gav);
	inline void SwapBuffers(std::vector<Member>*& population, std::vector<Member>*& buffer);

public:
	GeneticAlg(int r, int g, int b);
	std::array<int, 3> TargetColor;
	void RunAlgorithm();
};