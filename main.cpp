#include <iostream>                  // для cout и т.п.
#include <vector>                    // для класса vector
#include <algorithm>                 // для алгоритма сортировки
#include <time.h>                    // для случайных величин
#include <math.h>                    // для abs()
#include <array>


using namespace std;
#define GA_POPSIZE        2048        // размер популяции
#define GA_MAXITER        16384        // максимальное число итераций
#define GA_ELITRATE        0.10f        // элитарность
#define GA_MUTATIONRATE    0.25f            // мутации
#define GA_MUTATION        RAND_MAX * GA_MUTATIONRATE

using namespace std;

struct ga_struct
{
    array<int, 3> arr;                       // массив элеметов
    unsigned int fitness;                    // пригодность
};
typedef vector<ga_struct> ga_vector;            // для краткости

class Gen{
    array<int, 3> GA_TARGET = {96, 96, 159};
public:
    void init_population(ga_vector&, ga_vector&);
    void calc_fitness(ga_vector&);
    static bool fitness_sort(ga_struct x, ga_struct y);
    inline void sort_by_fitness(ga_vector &population);
    void elitism(ga_vector&, ga_vector&, int);
    void mutate(ga_struct &member);
    void mate(ga_vector &population, ga_vector &buffer);
    inline void print_best(ga_vector &gav);
    inline void swap(ga_vector *&population, ga_vector *&buffer);
    
    void run();
};

void Gen::init_population(ga_vector &population, ga_vector &buffer)
{
    int tsize = 3;

    for (int i=0; i<GA_POPSIZE; i++) {
        ga_struct citizen;
        
        citizen.fitness = 0;

        for (int j=0; j<tsize; j++)
            citizen.arr[j] = (rand() % 255);

        population.push_back(citizen);
    }

    buffer.resize(GA_POPSIZE);
}

void Gen::calc_fitness(ga_vector &population)
{
    array<int, 3> target = GA_TARGET;
    int tsize = target.size();
    unsigned int fitness;

    for (int i=0; i<GA_POPSIZE; i++) {
        fitness = 0;
        for (int j=0; j<tsize; j++) {
            fitness += abs(int(population[i].arr[j] - target[j]));
        }
        
        population[i].fitness = fitness;
    }
}

bool Gen::fitness_sort(ga_struct x, ga_struct y)
{ return (x.fitness < y.fitness); }

inline void Gen::sort_by_fitness(ga_vector &population)
{ sort(population.begin(), population.end(), Gen::fitness_sort); }

void Gen::elitism(ga_vector &population,
                ga_vector &buffer, int esize )
{
    for (int i=0; i<esize; i++) {
        buffer[i].arr = population[i].arr;
        buffer[i].fitness = population[i].fitness;
    }
}

void Gen::mutate(ga_struct &member)
{
    int tsize = GA_TARGET.size();
    int ipos = rand() % tsize;
    int delta = (rand() % 255);

    member.arr[ipos] = ((member.arr[ipos] + delta) % 255);
}

void Gen::mate(ga_vector &population, ga_vector &buffer)
{
    int esize = GA_POPSIZE * GA_ELITRATE;
    int tsize = GA_TARGET.size(), spos, i1, i2;

    elitism(population, buffer, esize);

    // Mate the rest
    for (int i=esize; i<GA_POPSIZE; i++) {
        i1 = rand() % (GA_POPSIZE / 2);
        i2 = rand() % (GA_POPSIZE / 2);
        spos = rand() % tsize;


        for (int j = 0; j < GA_TARGET.size(); j++)
        buffer[i].arr[j] = (population[i1].arr[j] & ((int)pow(2, 8) - (int)pow(2, spos))) | (population[i2].arr[j] & ((int)pow(2, spos) - 1));
            
        if (rand() < GA_MUTATION) mutate(buffer[i]);
    }
}

inline void Gen::print_best(ga_vector &gav)
{ cout << "Best: " << gav[0].arr[0]<< ", " << gav[0].arr[1] <<", " << gav[0].arr[2] << " (" << gav[0].fitness << ")" << endl; }

inline void Gen::swap(ga_vector *&population,
                 ga_vector *&buffer)
{ ga_vector *temp = population; population = buffer; buffer = temp; }

void Gen::run()
{
    setlocale (LC_ALL, "rus" );
    srand(unsigned(time(NULL)));

    ga_vector pop_alpha, pop_beta;
    ga_vector *population, *buffer;

    init_population(pop_alpha, pop_beta);
    population = &pop_alpha;
    buffer = &pop_beta;

    for (int i=0; i<GA_MAXITER; i++) {
        calc_fitness(*population);        // вычисляем пригодность
        sort_by_fitness(*population);        // сортируем популяцию
        print_best(*population);        // выводим лучшую популяцию

        if ((*population)[0].fitness == 0) break;

        mate(*population, *buffer);        // спариваем популяции
        swap(population, buffer);        // очищаем буферы
    }
}
int main(){
    Gen a;
    a.run();
    return 0;
}
