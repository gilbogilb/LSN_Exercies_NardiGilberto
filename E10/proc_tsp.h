//procedural tsp stuff for when classes don't work

//ONLY CALL SELECTION OPERATOR IF THE PLOPULATION IS ORDERED
#include <vector>
#include <iostream>
#include "random.h"
#include <cmath>
#include <algorithm>
using namespace std;

//vector<vector<int>> population;
Random local_rnd;

bool
TSPCheckPerm(vector<int>& indexes){


    //we need to check that the permutation has no repeated indexes.
    //coming back to the last city is automatic for how the cost function
    //is implemented (the last cost element is the distance between the last
    // and the first city). Also check that the first is one!

    if(indexes.at(0)!=0) return false;

    bool ok = true;
    for(auto it = indexes.begin(); it!= indexes.end(); ++it) {
        for(auto it2 = it+1; it2!=indexes.end(); ++it2) {
            if(*it==*it2) {
                ok = false;
                break;
            }
        }
    }

return ok;
}

void mutate_swap(vector<int>& p){
  //randomly select two eligible cities
    int i = (int)local_rnd.Rannyu(1.,p.size()),
        j = (int)local_rnd.Rannyu(1.,p.size()),
        tmp;
    
    //swap
    tmp = p.at(i);
    p.at(i) = p.at(j);
    p.at(j) = tmp;
}

void
mutate_shift(vector<int>& p){

    int shift = (int)local_rnd.Rannyu(1.,p.size()-2.),
        tmp;
    
    for(int i=1; i<p.size();++i){
        tmp = p.at(i)+shift;
        if(tmp>=p.size())
            p.at(i)=(p.at(i)+shift)%(p.size())+1;
        else
            p.at(i)=p.at(i)+shift;
    }

}

void
mutate_reverse(vector<int>& p){
    int first = local_rnd.Rannyu(1.,p.size()-1),
        last  = local_rnd.Rannyu(first+1,p.size()-1);
    
    double tmp;

    for(int i=0; i<(last-first)/2; ++i){
        tmp = p.at(i+first);
        p.at(i+first) = p.at(last-i);
        p.at(last-i) = tmp;
    }
    
}

void crossover(vector<int> p1, vector<int> p2){

  vector<int> son1, son2;

    //cutting the vectors
    int index_half = p1.size()/2;

    //copy the first half
    for (int i=0; i<index_half; ++i){
        son1.push_back(p1.at(i));
        son2.push_back(p2.at(i));
    }

    //swap the second - need to care that cities are not repeated
    int candidate; //candidate to be added to the sequence
    bool add;      //do we need to add this
    for(auto it=p1.begin()+1; it!=p1.end(); ++it){
        add = true;
        candidate = *it;
        for(int j=1; j<index_half; ++j){ //check if the city is already present
            if (p2.at(j)==candidate) add = false;
        }
        if(add) son2.push_back(candidate);
    }

    for(auto it=p2.begin()+1; it!=p2.end(); ++it){
        add = true;
        candidate = *it;
        for(int j=1; j<index_half; ++j){ //check if the city is already present
            if (p1.at(j)==candidate) add = false;
        }
        if(add) son1.push_back(candidate);
    }
    
    p2 = son2;
    p1 = son1;

}

double L2cost(vector<int> p, vector<vector<double>> cities) {

  if(p.size()!=cities.size()){
    cout << "error: proposed permutation vector size and city size are not equal\n" << p.size() << " " << cities.size() << std::endl;
    abort();
  }

  double cost = 0.;

  double dx = 0., dy = 0.;
  for(int i = 0; i<p.size()-1; ++i) {
      dx = cities.at( p.at(i+1) ).at(0)-cities.at( p.at(i) ).at(0);
      dy = cities.at( p.at(i+1) ).at(1)-cities.at( p.at(i) ).at(1);
      cost += pow(dx,2) + pow(dy,2);
  }
  dx = cities.at( p.at(0) ).at(0)-cities.at( p.at(p.size()-1) ).at(1);
  dy = cities.at( p.at(0) ).at(1)-cities.at( p.at(p.size()-1) ).at(1);
  cost += pow(dx,2) + pow(dy,2);

  return cost;
}

vector<int>
select(vector<vector<int>> pop,vector<vector<double>> cities) { //warning - use it with ordered populations
    //supposedly max & min are already calculated (automatically happens when a new generation or the first gen is made).

    double pexp = 2.;
    int random_index;
    
    double cost, prob, r=local_rnd.Rannyu();
    do{
        random_index = (int)local_rnd.Rannyu(0.,pop.size());

        cost = L2cost(pop.at(random_index),cities );
        double min_cost = L2cost(pop.at(0),cities);
        double max_cost= L2cost(pop.at(pop.size()-1),cities);
        prob = pow((cost-max_cost)/(min_cost-max_cost),pexp);

    }while(r>prob);

return pop.at(random_index);
    
}

vector<vector<double>> 
cities_in_square(int cities_number) //this uses a generator in its own scope to have always the same cities.
{  //NB seed used is seed.in

    Random rnd;
    rnd.Initialize();
    vector<double> city = {0.,0.};
    vector<vector<double>> cities;

    for( int i=0; i<cities_number; ++i ){
        city.at(0) = rnd.Rannyu();
        city.at(1) = rnd.Rannyu();
        cities.push_back(city);
    }
    std::cout << "preprared cities over a square\n";
    return cities;
}

//functor to use std::sort()
class TSPSorter {
    public:
    TSPSorter(vector<vector<double>> cities): m_cities(cities){}
    ~TSPSorter(){}
    bool operator()(vector<int> i, vector<int> j) {
        if( (L2cost(i,m_cities)) < (L2cost(j,m_cities)) )
            return true;
        else
            return false;
    }
    private:
        vector<vector<double>> m_cities;
};

vector<vector<int>> generate_population(int population_size, vector<vector<double>> cities){

  vector<int> sample;
  vector<vector<int>> pop;
  for(int i=0; i<cities.size(); ++i) sample.push_back(i); //range(0,genes-1)

  for(int i=0; i<population_size; ++i){

    //mutate from the initial sample vector
    vector<int> tmp = sample;
    for(int j=0; j<tmp.size(); ++j){
      mutate_swap(tmp); 
      mutate_reverse(tmp);
    }
        
    if(TSPCheckPerm(tmp)) pop.push_back(tmp);
      else {
        cout << "found an invalid permutation\n";
        for(auto it=tmp.begin(); it!=tmp.end();++it) std::cout << *it << " ";
        std::cout << std::endl;
      }
    }

    //sort the new population
    TSPSorter comparator(cities);
    sort(pop.begin(),pop.end(),comparator);

  return pop;
}

void make_generation(vector<vector<int>>& pop, vector<vector<double>> cities,double pc, double pm1, double pm2, double pm3){

  vector<vector<int> > new_pop;
  vector<int> parent1, parent2;

    //make sons
    //std::cout << "starting to make kids\n";
    while(new_pop.size()<pop.size()){

        //std::cout << "making kids new_pop.size()=" << new_pop.size() << ", m_population.size()=" << m_population.size() << std::endl; 
        parent1 = select(pop,cities);
        parent2 = select(pop,cities);

        //std::cout << "selected parents - ";
        if(local_rnd.Rannyu()<pc) {
          crossover(parent1,parent2);
        }

        new_pop.push_back(parent1);
        new_pop.push_back(parent2);
     
    }
    //std::cout << "done new population\n";
    //std::cout << "starting to mutate\n";
    //mutate the new generation
    for(auto it = new_pop.begin(); it!=new_pop.end(); ++it){
        if(local_rnd.Rannyu()<pm1) mutate_swap(*it);
        if(local_rnd.Rannyu()<pm2) mutate_shift(*it);
        if(local_rnd.Rannyu()<pm3) mutate_reverse(*it);
    }

    //std::cout << "checking perm\n";
    for (auto it= new_pop.begin(); it!=new_pop.end(); ++it)
        if(!TSPCheckPerm(*it)) cout << "warning: found an illicit permutation in the making of a new generation.\n ";
    
    pop = new_pop;

    //std::cout << "sorting\n";
    TSPSorter comparator(cities);
    sort(pop.begin(),pop.end(),comparator);

}