
#include "Problem.h"
#include <iostream>

using namespace std;

Problem::Problem()
{
}
Problem::~Problem()
{
}

Problem::Problem(const Problem& pbm)
{
	*this = pbm;
}

ostream& operator << (ostream& os, const Problem& pr)
{
	os << "Dimension: " << pr._dimension << " numero Problem: "<< pr.numProblem << " Lower limite: " << pr.LowerLimit << " Upper limite: " << pr.UpperLimit;
	return os;
}

istream& operator >> (istream& is,  Problem& pr )
{
	cout << "Numero de Probleme: " << endl << "1: Rosenbrock" << endl << "2: Rastrigin "<< endl <<"3: ackley"<< endl <<"4: schwefel "<< endl <<"5: schaffer "<< endl <<"6: weierstrass" << endl << "==>";
    is >> pr.numProblem;
	cout << "La Dimension: " << endl <<"==>";
	is >> pr._dimension;
	cout << "lower limite: " << endl << "==>";
	is >> pr.LowerLimit;
	cout << "Upper limite: " << endl << "==>";
	is >> pr.UpperLimit;
	return is;
}

Problem& Problem::operator=(const Problem& pb)
{
	if (this != &pb)
	{
		UpperLimit = pb.UpperLimit;
		LowerLimit = pb.LowerLimit;
		_dimension = pb.dimension();
		numProblem = pb.numProblem;
	}
	return *this;
}

bool Problem::operator ==(const Problem& pb) const
{
	return (pb._dimension == _dimension) && (pb.numProblem == numProblem);
}

bool Problem::operator!=(const Problem& pb) const
{
	return (pb._dimension != _dimension) && (pb.numProblem != numProblem);
}

int Problem::dimension() const
{
	return _dimension;
}

