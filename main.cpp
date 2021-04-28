#include <iostream>  
#include <Windows.h>                  
#include <time.h>                    

#include "GeneticAlg.h"

int main() 
{
	setlocale(LC_ALL, "rus");
	srand(unsigned(time(NULL)));
	
	int r, g, b ;
	std::cout << "¬ведите необходимый цвет в формате RGB:" << std::endl;
	std::cin >> r >> g >> b;

	GeneticAlg a(r, g, b);
//	GeneticAlg a(96,96,159);
	a.RunAlgorithm();


	std::cin.get();
	return 0;
}