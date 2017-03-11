
#include "MyAlgorithm.h"
#include <iterator>

#define CR 0.6
#define F 0.42

MyAlgorithm::MyAlgorithm(const Problem& pbm, const SetUpParams& setup) :

_solutions(setup.population_size()), _fitness_values(setup.population_size()),
_setup((SetUpParams)setup), _upper_cost(), _lower_cost(), _pbm(pbm)
{
	initialize();
}

 

MyAlgorithm::~MyAlgorithm() {
	_solutions.~vector();
	_fitness_values.~vector();
}

 

ostream& operator << (ostream& os, const MyAlgorithm& myAlgo) {

 

 os << myAlgo._setup << endl;

 

 vector<Solution*>::const_iterator it = myAlgo._solutions.begin();

 for (; it != myAlgo._solutions.end(); ++it)

 {

   os << *(*it) << endl;

 }

 



 for (unsigned int i = 0; i < myAlgo._fitness_values.size(); i++)

 {

   os << "index : " <<myAlgo._fitness_values[i].index << "fitness : " << myAlgo._fitness_values[i].fitness << endl;

 }

 

 os << "best value : " << myAlgo._lower_cost << endl;

 return os;

}

 

istream& operator >> (istream& is, MyAlgorithm& myAlgo) {

	return is;

}

 

MyAlgorithm& MyAlgorithm::operator = (const MyAlgorithm& myAlgo) {

 if (&myAlgo != this)

 {

   _solutions = myAlgo._solutions;

   _fitness_values = myAlgo._fitness_values;

   _setup = myAlgo._setup;

   _upper_cost = myAlgo._upper_cost;

   _lower_cost = myAlgo._lower_cost;

 }

 return *this;

}

 

SetUpParams& MyAlgorithm::setup()  {

 return _setup;

}

 

void MyAlgorithm::initialize() {

 vector<Solution*>::iterator it2 = _solutions.begin();
 vector<struct  particle>::iterator itv = _fitness_values.begin();
 for (int i=0; it2 != _solutions.end(); ++it2,i++,++itv)
 {
	 struct particle st;
	 *it2 = new Solution(_pbm);
	 (*(*it2)).initialize();
	 st.index = i;
	 st.fitness = (*(*it2)).get_fitness();
	 *itv = st;
 }
}

 

void MyAlgorithm::runDEA() {

  vector<Solution*>::const_iterator it = _solutions.begin();
  vector<double>::iterator ita ;
  vector<double>::iterator itb;
  vector<double>::iterator itc;
  vector<double>::iterator itx;
  vector<struct  particle>::iterator itv =  _fitness_values.begin();
 int ind_x = 0;
 Solution s1(solution(ind_x));
 Solution a(solution(ind_x));
 Solution b(solution(ind_x));
 Solution c(solution(ind_x));
 Solution& x=solution(ind_x);
 for (; it != _solutions.end(); ++it)
 {
   //x = (*(*it)); // j'ai ajouter une reference comme sa si on modifier le x sa sera modifier aussi dans le vector
   int ind_a, ind_b, ind_c;
   do
   {
     ind_a = ((double)rand() / (double)RAND_MAX) *((double) _setup.population_size() - 1);
   } while (ind_a == ind_x);

   do
   {
     ind_b = ((double)rand() / (double)RAND_MAX) *((double) _setup.population_size() - 1);
   } while (ind_b == ind_x || ind_b == ind_a);

   do
   {
     ind_c = ((double)rand() / (double)RAND_MAX) *((double) _setup.population_size() - 1);
   } while (ind_c == ind_x || ind_c == ind_b || ind_c == ind_a);

   a = solution(ind_a);
   b = solution(ind_b);
   c = solution(ind_c);

   int r = (rand() % (*(*it)).pbm().dimension()) + 1;
   ita = a.solution().begin();
   itb = b.solution().begin();
   itc = c.solution().begin();
   itx = (*(*it)).solution().begin();
   for (int i=0; ita < a.solution().end(); ++ita,++itb,++itc,i++)
   {
     double u = ((double)rand()) / RAND_MAX;
     if (u < CR || (i == r - 1))
     {	 
       s1.position(i,*ita + F * (*itb - *itc));
     }
     else
     {
       s1.position(i,*itx);
     }
   }
   s1.fitness();
   if ( s1.get_fitness() < (*(*it)).get_fitness())
   {
	   (*(*it)) = s1;
   }
   for(;itv != _fitness_values.end(); ++itv)
   {
	   if((*itv).index == ind_x )
	   {
		   (*itv).fitness =(*(*it)).get_fitness();
		   break;
	   }
   }
   itv = _fitness_values.begin();
   ind_x++;
 }
}

 

void MyAlgorithm::evaluate() {

 vector<Solution*>::const_iterator it = _solutions.begin();

 for (; it != _solutions.end(); ++it)

 {

   (*(*it)).fitness();

 }

}

 

const vector<Solution*>& MyAlgorithm::solutions() const {

 return _solutions;

}

 

unsigned int MyAlgorithm::upper_cost() const {

 return _upper_cost;

}

 

unsigned int MyAlgorithm::lower_cost() const {

 return _lower_cost;

}

 

Solution& MyAlgorithm::solution(const unsigned int index) const {

 return *(_solutions[index]);

}

 

vector<struct particle>& MyAlgorithm::fitness_values() {

 return _fitness_values;

}

 

double MyAlgorithm::fitness(const unsigned int index) const {

 return _fitness_values[index].fitness;

}

 

double MyAlgorithm::best_cost() const {

 return 0;

}

 

double MyAlgorithm::worst_cost() const {

 return 0;

}

 

Solution MyAlgorithm::best_solution() const {

 vector<struct particle>::const_iterator it = _fitness_values.begin();

 struct particle best = (*it);

 for (; it != _fitness_values.end(); ++it)

 {

   if ((*it).fitness < best.fitness)

   {

     best = (*it);

   }

 }
 return *(_solutions[best.index]);

}

 

Solution& MyAlgorithm::worst_solution() const {

 vector<struct particle>::const_iterator it = _fitness_values.begin();

 struct particle worst = (*it);

 for (; it != _fitness_values.end(); ++it)

 {

   if ((*it).fitness > worst.fitness)

   {

     worst = (*it);

   }

 }

 return *(_solutions[worst.index]);

}

 

void MyAlgorithm::evolution() {

 for (unsigned int i = 0; i < _setup.nb_evolution_steps(); i++)

 {
     evaluate();
     runDEA();
 }
 std::cout << std::scientific <<endl;
 std::cout << best_solution() << std::endl;
}