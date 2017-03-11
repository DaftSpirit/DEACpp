#ifndef SOLUTION_H
#define SOLUTION_H

#include "Problem.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

struct particle // index of a particle in the swarm and its fitness
{
	int index;
	double fitness;
};

class Solution
{
	//contient la d?claration d'une solution
public:
	Solution(const Problem& pbm);
	Solution(const Solution& sol);
	~Solution();

	friend ostream& operator<< (ostream& os, const Solution& sol);
	friend istream& operator>> (istream& is, Solution& sol);

	Problem& pbm();

	Solution& operator=  (const Solution& sol);
	bool operator== (const Solution& sol) const;
	bool operator!= (const Solution& sol) const;

	void initialize();
	double fitness(); //Fct d'obj, implémenter les différentes fct avec un switch
	double get_fitness();

	unsigned int size() const;

	vector<double>& solution();

	double& position(const int index); //retournera une position du tableau _solution
	void  position(const int index, const double value);
	Problem _pbm;

private:
	vector<double> _solution;
	double _current_fitness;
	
	double Rosenbrock();
	double Rastrigin();
	double Ackley();
	double Schwefel();
	double Schaffer();
	double Weierstrass();
	double testFunction();
};

#endif