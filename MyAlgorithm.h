#ifndef MYALGORITHM_H
#define MYALGORITHM_H

#include "Problem.h"
#include "Solution.h"
#include "SetUpParams.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#define SOL 30

using namespace std;

class MyAlgorithm
{
private:
	vector<Solution*> _solutions;     // individuals in population
	vector<struct particle> _fitness_values;
	SetUpParams _setup;
	Problem _pbm;
	unsigned int _upper_cost, _lower_cost; // lower and upper fitness of individuals in population
	//double fitnesses[SOL]; // groups of all fintesses of all solutions

public:
	MyAlgorithm(const Problem&, const SetUpParams& setup);
	~MyAlgorithm();

	friend ostream& operator<< (ostream& os, const MyAlgorithm& myAlgo);
	friend istream& operator>> (istream& is, MyAlgorithm& myAlgo);
	MyAlgorithm& operator= (const MyAlgorithm& myAlgo);
	SetUpParams& setup() ;
	void initialize();

	// creates a array with fitness of all solutions in MyAlgorithm and its position in the MyAlgorithm
	void evaluate();

	const vector<Solution*>& solutions() const;
	unsigned int upper_cost() const;
	unsigned int lower_cost() const;
	Solution& solution(const unsigned int index) const;
	vector<struct particle>&  fitness_values();
	double fitness(const unsigned int index) const;


	double best_cost() const;
	double worst_cost() const;
	Solution best_solution() const;
	Solution& worst_solution() const;

	void evolution(); /*makes an evolution step*/
	void runDEA(); /* runs diferential evolution algorithm */

};

#endif