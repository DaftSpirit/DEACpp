
#include "Solution.h"

Solution::Solution(const Problem& pbm) :
_solution(pbm.dimension()), _current_fitness(), _pbm(pbm)
{}

Solution::Solution(const Solution& sol) :
_solution(sol._solution.size()), _current_fitness(sol._current_fitness), _pbm(sol._pbm)
{
	for (unsigned int i = 0; i < _solution.size(); i++)
	{
		_solution[i] = sol._solution[i];
	}
}

Solution::~Solution() {
	_solution.~vector();
}

ostream& operator << (ostream& os, const Solution& sol) {
	os << "Solution : ";
	for (unsigned int i = 0; i < sol._solution.size(); i++) {
		os << endl << sol._solution[i];
	}
	os << endl << "Fitness actuelle : " << sol._current_fitness << endl
		<< "Type de problème : "<<endl<< sol._pbm << endl;

	return os;
}

istream& operator >> (istream& is, Solution& sol) {
	return is;
}

Problem& Solution::pbm() {
	return _pbm;
}

Solution& Solution::operator = (const Solution& sol) {
	if (this != &sol) {
		vector<double>::const_iterator it = sol._solution.begin();
		vector<double>::iterator it1 = _solution.begin();
		for (; it != sol._solution.end(); ++it, ++it1)
		{
			*it1 = *it;
		}
		_current_fitness = sol._current_fitness;
		_pbm = sol._pbm;
	}
	return *this;
}

bool Solution::operator == (const Solution& sol) const {
	return ((_solution == sol._solution) && (_current_fitness == sol._current_fitness) 
		&& (_pbm == sol._pbm));
}

bool Solution::operator != (const Solution& sol) const {
	return !((_solution == sol._solution) && (_current_fitness == sol._current_fitness)
		&& (_pbm == sol._pbm));
}

void Solution::initialize() {
	vector<double>::iterator it = _solution.begin();
	for (; it != _solution.end(); it++) {
		*it =(int)( (((double)rand()/RAND_MAX) * _pbm.UpperLimit) + _pbm.LowerLimit);
	}
}

double Solution::fitness() {
	switch (_pbm.numProblem) {
	case 0:
		_current_fitness = testFunction();
		return _current_fitness;
	case 1: //Rosenbrock
		_current_fitness = Rosenbrock();
		return _current_fitness;

	case 2: //Rastrigin
		_current_fitness = Rastrigin();
		return _current_fitness;

	case 3: //Ackley
		_current_fitness = Ackley();
		return _current_fitness;

	case 4: //Schwefel
		_current_fitness = Schwefel();
		return _current_fitness;

	case 5: //Schaffer
		_current_fitness = Schaffer();
		return _current_fitness;

	case 6: //Weierstrass
		_current_fitness = Weierstrass();
		return _current_fitness;

	}
}

double Solution::get_fitness() {
	return _current_fitness;
}

double Solution::Rosenbrock() {
	double sum = 0;

	for (int i = 0; i<_pbm.dimension() - 1; ++i) {
		float temp = 100 * (_solution[i] * _solution[i] - _solution[i + 1])*
			(_solution[i] * _solution[i] - _solution[i + 1]) + (_solution[i] - 1)*(_solution[i] - 1);
		sum += temp;
	}

	return sum;
}

double Solution::Rastrigin() {
	const double omega = 2.0 * 3.1415;
	double sum = 0;

	for (unsigned int i = 0; i < _pbm.dimension(); ++i) {
		sum += _solution[i] * _solution[i] - 10.0 * std::cos(omega * _solution[i]);
	}

	return sum += 10.0 * _pbm.dimension();
}

double Solution::Ackley() {
	double sum = 0;
	double omega = 2.0 * 3.1415;
	double s1 = 0.0, s2 = 0.0;
	double nepero = exp(1.0);

	for (std::vector<double>::size_type i = 0; i<_pbm.dimension(); i++){
		s1 += _solution[i] * _solution[i];
		s2 += cos(omega*_solution[i]);
	}

	return sum = -20 * exp(-0.2 * sqrt(1.0 / _pbm.dimension() * s1)) - exp(1.0 / _pbm.dimension() * s2) + 20 + nepero;
}

double Solution::Schwefel() {
	double value = 0;
	double sum = 0;

	for (std::vector<double>::size_type i = 0; i<_pbm.dimension(); i++){
		value += _solution[i] * sin(sqrt(fabs(_solution[i])));
	}
	return sum = 418.9828872724338 * _pbm.dimension() - value;
}

double Solution::Schaffer() {
	double sum = 0;
	double s1 = 0.0, s2 = 0.0;

	for (std::vector<double>::size_type i = 0; i<_pbm.dimension(); i++){
		s1 -= _solution[i] * _solution[i];
		s2 += _solution[i] * _solution[i];
	}

	return sum = 0.5 + (sin(s1) * sin(s1) - 0.5) / ((1 + 0.001 * s2)*(1 + 0.001 * s2));
}

double Solution::Weierstrass() {
	//on prend ici comme coefficients a = 0.5 et b = 9
	double pi = 3.1415;
	double a = 0.5;
	double b = 9;
	double sum = 0;

	for (int i = 0; i<_pbm.dimension(); ++i) {
		float temp = pow(a, i) * cos(pow(b, i) * pi * _solution[i]);
		sum += temp;
	}

	return sum;
}

double Solution::testFunction() {
	double r = 0;
	for (int i = 0; i < _pbm.dimension(); i++)
	{
		r += _solution[i] * _solution[i];
	}
	return r;
}


unsigned int Solution::size() const {
	return _solution.size();
}

vector<double>& Solution::solution() {
	return _solution;
}

double& Solution::position(const int index) {
	return _solution[index];
}

void  Solution::position(const int index, const double value) {
	_solution[index] = value;
}