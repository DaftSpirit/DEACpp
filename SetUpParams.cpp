
#include "SetUpParams.h"

SetUpParams::SetUpParams() :
_independent_runs(0), _nb_evolution_steps(0), _population_size(0), _solution_size(0)
{}

SetUpParams::SetUpParams(const SetUpParams& setup) :
_independent_runs(setup._independent_runs), _nb_evolution_steps(setup._nb_evolution_steps), _population_size(setup._population_size), _solution_size(setup._solution_size)
{}

SetUpParams::~SetUpParams() {

}

SetUpParams& SetUpParams::operator = (const SetUpParams& setup) {
	     if(this != & setup)
		 {
        _independent_runs = setup.independent_runs();
        _nb_evolution_steps = setup.nb_evolution_steps();
        _population_size = setup.population_size();
		 }
       // _solution_size = setup.solution_size();

        return *this;
}

ostream& operator << (ostream& os, const SetUpParams& setup) {

    return os << setup._independent_runs << setup._nb_evolution_steps << setup._population_size << setup._solution_size;
}

istream& operator >> (istream& is, SetUpParams& setup) {
	cout << endl << "Enter independent_runs : ";
	is >> setup._independent_runs;
	cout << endl << "Enter nb_evolution_steps : ";
	is >> setup._nb_evolution_steps;
	cout << endl << "Enter population_size : ";
	is >> setup._population_size;
	return is;
}

const unsigned int SetUpParams::independent_runs() const {
    return _independent_runs;
}

const unsigned int SetUpParams::nb_evolution_steps() const {
    return _nb_evolution_steps;
}

const unsigned int SetUpParams::population_size() const {
    return _population_size;
}

const unsigned int SetUpParams::solution_size() const {
    return _solution_size;
}

void SetUpParams::independent_runs(const unsigned int val) {
    _independent_runs = val;
}

void SetUpParams::nb_evolution_steps(const unsigned int val) {
    _nb_evolution_steps = val;
}

void SetUpParams::population_size(const unsigned int val) {
    _population_size = val;
}

void SetUpParams::solution_size(const unsigned int val) {
    _solution_size = val;
}
