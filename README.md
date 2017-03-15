# DEACpp
Implementation of differential evolution algorithm in C++
This implementation is made to be tested with typical graphs of typical funcitons such as [Rastrigin](https://en.wikipedia.org/wiki/Rastrigin_function) or [Rosenbrock](https://en.wikipedia.org/wiki/Rosenbrock_function)

# Code explanation

## 3.1 Set up Params
This class contains all the parameters necessary for a good run of the simulation and the algorithm

## 3.2 Problem
This class contains the different existing choices of parameters and problems (definition domain for example)

## 3.3 Solution
This class contains the implementation of vectors representing solutions of the problem and some benchmarks necessary to test our implementation efficiency

## 3.4 MyAlgorithm
This class contains the DEA implementation
```C++
void MyAlgorithm::runDEA() {
  vector<Solution*>::const_iterator it = _solutions.begin();
  vector<double>::iterator ita ;
  vector<double>::iterator itb;
  vector<double>::iterator itc;
  vector<double>::iterator itx;
  vector<struct particle>::iterator itv = _fitness_values.begin();
  int ind_x = 0;

  Solution s1(solution(ind_x));
  Solution a(solution(ind_x));
  Solution b(solution(ind_x));
  Solution c(solution(ind_x));
  Solution& x=solution(ind_x);
  for (; it != _solutions.end(); ++it)
  {
    x = (*(*it)); // j’ai ajouter une reference comme sa si on modifier le x sa sera modifier aussi dans le vector
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
    int r = (rand() % x.pbm().dimension()) + 1;
    ita = a.solution().begin();
    itb = b.solution().begin();
    itc = c.solution().begin();
    itx = x.solution().begin();
    for (int i=0; ita < a.solution().end(); ++ita,++itb,++itc,i++)
    {
      double u = rand() / RAND_MAX;
      if (u < CR || (ita - a.solution().begin()) == r - 1)
      {
        s1.position(i,*ita + F * (*itb - *itc));
      }
      else
      {
        s1.position(i,*itx);
      }
    }

    s1.fitness();
    x = (s1.get_fitness()<x.get_fitness())? s1:x;
    for(;itv != _fitness_values.end(); ++itv)
    {
      if((*itv).index == ind_x)
      {
        (*itv).fitness =x.get_fitness();
        break;
      } 
    }
    itv = _fitness_values.begin();
    ind_x++;
  }
}
```

## Sources

* [Differential Evolution Algorithm](https://en.wikipedia.org/wiki/Differential_evolution)
