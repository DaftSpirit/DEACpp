// DEA.cpp : définit le point d'entrée pour l'application console.
//


#include "MyAlgorithm.h"
#include "Problem.h"
#include "SetUpParams.h"
#include "Solution.h"
#include <iostream>

void deaMain()
{
	Problem p;
	std::cin >> p;
	SetUpParams setUp;
	std::cin >> setUp;
	
	MyAlgorithm dea(p, setUp);
	vector<double> runs(dea.setup().independent_runs());
	for (unsigned int i = 0; i < dea.setup().independent_runs(); i++)
	{
		dea.evolution();
		runs[i] = dea.best_solution().get_fitness();
		dea.initialize();
	}
	/* moyenne et ecart type best solution */
	vector<double>::iterator itBest = runs.begin();
	double meanBest = 0;
	for (; itBest != runs.end(); ++itBest)
	{
		meanBest += (*itBest);
	}
	double meanBestmoy = (meanBest / (double)runs.size());

	double ecarTypeBest;
	double sum = 0;
	itBest = runs.begin();
	for (; itBest != runs.end(); ++itBest)
	{
		sum += ((*itBest) - meanBestmoy)*((*itBest) - meanBestmoy);
	}
	ecarTypeBest = sqrt((1.0 /(double) runs.size())*sum);

	std::cout << "Moyenne sur les runs :" << std::endl << meanBestmoy << std::endl;
	std::cout << "Ecart Type sur les runs :" << std::endl << ecarTypeBest << std::endl;

}

int main(int argc, char* argv[])
{
	deaMain();
	return 0;
}

