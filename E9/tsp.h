///////////////////////////////////////////////////////////////
//Header file containing a useful definition and instantiation
//of class(es) for the Travelling Salesman Problem (TSP)
//
//author: gilberto.nardi@studenti.unimi.it
//  date: May 25th, 2021
//
///////////////////////////////////////////////////////////////

#ifndef TSP_H
#define TSP_H

#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

#include "random.h"

//simple position class
class point2D {

	public:
		point2D(double x, double y): m_x(x), m_y(y) {};
		point2D(): m_x(0), m_y(0) {};
        point2D(const point2D& p): m_x(p.GetX()), m_y(p.GetY()) {};
		~point2D(){};
		
		double distance (point2D& p) const {return sqrt( pow(m_x-p.GetX(),2) + pow(m_y-p.GetY(),2) );};
		
		double GetX() const {return m_x;};
		double GetY() const {return m_y;};
		
		void SetX(double x) {m_x=x;};
		void SetY(double y) {m_y=y;};
		
	protected:
	
		double m_x, m_y;

};

//tsp problem class
class TSP {

    public:
        TSP(int size): m_size(size), m_ready(false){};
        ~TSP(){};

        void PrepareCircumference(); //cities distributed on a circle
        void PrepareSquare();        //cities distributed in a square
        void PrepareTest();          //4 cities at the vertices of a square

        //cost functions
        double L2cost(std::vector<int>& indexes);

        //get members
        double GetSize() const {return m_size;}
        bool   IsReady() const {return m_ready;}
        std::vector<point2D> GetCities() const {return m_cities;}

        //utilities
        void WriteCities(const char* filename);
        void PrintPerm(std::vector<int> p); //prints the permutation and its cost

    protected:
        int m_size;
        std::vector<point2D> m_cities; //position of the cities
        bool m_ready;                  //is the TSP ready (has a configuration
                                       //of cities already been defined) ?

};

//functor to use std::sort()
class TSPSorter {
    public:
    TSPSorter(TSP* prob): m_TSP(prob){}
    ~TSPSorter(){}
    bool operator()(std::vector<int> i, std::vector<int> j) {
        if( (m_TSP->L2cost(i)) < (m_TSP->L2cost(j)) )
            return true;
        else
            return false;
    }
    private:
        TSP* m_TSP;
};

//genetic algorithm approach to solve TSP
class GeneticTSP : public TSP{

    public:
        GeneticTSP(int pop_size, int cities, char cities_distr); //char: C on a circumference, S over a square, T test
        ~GeneticTSP(){}

        //genetic alg operators
        void MutationSwap(std::vector<int>&);
        void MutationShift(std::vector<int>&);
        void MutationReverse(std::vector<int>&);
        void MutationSwapBlock(std::vector<int>&);
        void Crossover(std::vector<int>&, std::vector<int>&); //makes two kids from two parents
        std::vector<int> Select(); //selects a vector to crossover with a certain probability inversely related to the cost
        void MakeGeneration(double pc, double pm1, double pm2, double pm3);

        //utilities
        double BestHalfCost();  //returns the mean of the costs of the best half of the population
        void PrintPopulation(); //prints the permutation and their cost

        //get members
        std::vector<std::vector<int>> GetPop() const {return m_population;}
        double GetMinCost() const {return m_min_cost;}
        double GetMaxCost() const {return m_max_cost;}

    private:
        std::vector< std::vector<int> > m_population;
        double m_max_cost, m_min_cost;
        Random m_rnd;
        TSPSorter m_comparator;

};

//checks if the permutation is allowed by the "rules" of TSP
bool
TSPCheckPerm(std::vector<int>& indexes){

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

void
TSP::PrepareCircumference(){

    Random rnd;
    rnd.Initialize();
    double theta;
    point2D city;

    for( int i=0; i<m_size; ++i ){
        theta = rnd.Rannyu(0.,2*M_PI);
        city.SetX(cos(theta));
        city.SetY(sin(theta));
        m_cities.push_back(city);
    }

    std::cout << "preprared cities on a circumference\n";
    m_ready = true;
}

void
TSP::PrepareSquare(){

    Random rnd;
    rnd.Initialize();
    point2D city;

    for( int i=0; i<m_size; ++i ){
        city.SetX(rnd.Rannyu());
        city.SetY(rnd.Rannyu());
        m_cities.push_back(city);
    }

    std::cout << "preprared cities over a square\n";
    m_ready = true;
}

void
TSP::PrepareTest(){ //very simple distribution: 4 cities at the vertices of a 1x1 square

    m_size=4;
    point2D p(0,0), q(1,0), r(1,1), s(0,1);
    m_cities.push_back(p);
    m_cities.push_back(q);
    m_cities.push_back(r);
    m_cities.push_back(s);

    m_ready=true;
}

double 
TSP::L2cost(std::vector<int>& indexes){

    if(!m_ready){
        std::cerr << "you have called L2cost() without having generated a distribution of cities! (m_ready==false). End" << std::endl;
        exit(1);
    }

    double cost = 0.;

    if(indexes.size()!=m_cities.size()){
        std::cerr << "error: proposed permutation vector size and city size are not equal\n" << indexes.size() << " " << m_cities.size() << std::endl;
        return 0.;
    }

    double dx = 0., dy = 0.;
    for(int i = 0; i<m_size-1; ++i) {
        dx = m_cities.at( indexes.at(i+1) ).GetX()-m_cities.at( indexes.at(i) ).GetX();
        dy = m_cities.at( indexes.at(i+1) ).GetY()-m_cities.at( indexes.at(i) ).GetY();
        cost += pow(dx,2) + pow(dy,2);
    }
    dx = m_cities.at( indexes.at(0) ).GetX()-m_cities.at( indexes.at(m_size-1) ).GetX();
    dy = m_cities.at( indexes.at(0) ).GetY()-m_cities.at( indexes.at(m_size-1) ).GetY();
    cost += pow(dx,2) + pow(dy,2);

    return cost;
}

//generates a starting population
GeneticTSP::GeneticTSP(int pop_size, int cities, char cities_distr): TSP(cities), m_comparator(this) {

    m_rnd.Initialize();
    if(cities_distr=='C') PrepareCircumference();
    else if (cities_distr=='S') PrepareSquare();
    else if (cities_distr=='T') PrepareTest();
    else {
        std::cerr << "unrecognized city distribution character - end\n";
        exit(1);
    }

    std::vector<int> sample;
    for(int i=0; i<m_size; ++i) sample.push_back(i); //range(0,genes-1)

    for(int i=0; i<pop_size; ++i){

        //mutate from the initial sample vector
        std::vector<int> tmp = sample;
        for(int j=0; j<m_size; ++j){
            MutationSwap(tmp); 
            MutationShift(tmp);
        }
        
        if(TSPCheckPerm(tmp)) m_population.push_back(tmp);
        else {
            std::cerr << "found an invalid permutation\n";
            for(auto it=tmp.begin(); it!=tmp.end();++it) std::cout << *it << " ";
            std::cout << std::endl;
        }
    }

    std::sort(m_population.begin(),m_population.end(),m_comparator);
    m_min_cost = L2cost(m_population.at(0));
    m_max_cost = L2cost(m_population.at(m_population.size()-1));
}

void GeneticTSP::MakeGeneration(double pc, double pm1, double pm2, double pm3){
    
    std::vector<std::vector<int> > new_pop;
    std::vector<int> parent1, parent2;

    //make sons
    while(new_pop.size()<m_population.size()){

        //std::cout << "making kids new_pop.size()=" << new_pop.size() << ", m_population.size()=" << m_population.size() << std::endl; 
        parent1 = Select();
        parent2 = Select();

        //std::cout << "selected parents - ";
        if(m_rnd.Rannyu()<pc) Crossover(parent1,parent2);

        new_pop.push_back(parent1);
        new_pop.push_back(parent2);
     
    }
    //mutate the new generation
    for(auto it = new_pop.begin(); it!=new_pop.end(); ++it){
        if(m_rnd.Rannyu()<pm1) MutationSwap(*it);
        if(m_rnd.Rannyu()<pm2) MutationShift(*it);
        if(m_rnd.Rannyu()<pm3) MutationReverse(*it);
    }

    for (auto it= new_pop.begin(); it!=new_pop.end(); ++it)
        if(!TSPCheckPerm(*it)) std::cerr << "warning: found an illicit permutation in the making of a new generation.\n ";
    
    m_population = new_pop;

    std::sort(m_population.begin(),m_population.end(),m_comparator);

    //std::cout << " and sorted\n";
    m_min_cost = L2cost(m_population.at(0));
    m_max_cost = L2cost(m_population.at(m_population.size()-1));
    //std::cout << " min, max assigned. Done \n";
}

///////////////////////////////////////////////////
///////////////////MUTATIONS///////////////////////
///////////////////////////////////////////////////

void 
GeneticTSP::MutationSwap(std::vector<int>& starter){

    //randomly select two eligible cities
    int i = (int)m_rnd.Rannyu(1.,m_size),
        j = (int)m_rnd.Rannyu(1.,m_size),
        tmp;
    
    //swap
    tmp = starter.at(i);
    starter.at(i) = starter.at(j);
    starter.at(j) = tmp;

}
void
GeneticTSP::MutationShift(std::vector<int>& starter){

    int shift = (int)m_rnd.Rannyu(1.,m_size-2.),
        tmp;
    
    for(int i=1; i<m_size;++i){
        tmp = starter.at(i)+shift;
        if(tmp>=m_size)
            starter.at(i)=(starter.at(i)+shift)%(m_size)+1;
        else
            starter.at(i)=starter.at(i)+shift;
    }

}

void
GeneticTSP::MutationReverse(std::vector<int>& starter){
    int first = m_rnd.Rannyu(1.,starter.size()-1),
        last  = m_rnd.Rannyu(first+1,starter.size()-1);
    
    double tmp;
    //std::cout << "first = " << first << ", last = " << last << " (last-first)/2 = " << (last-first)/2 << std::endl;

    for(int i=0; i<(last-first)/2; ++i){
        tmp = starter.at(first+i);
        starter.at(first+i) = starter.at(last-i);
        starter.at(last-i) = tmp;
        //std::cout << "i=" << i << ", tmp = " << tmp << ", at(first+i)=" << starter.at(first+i) << ", starter.at(last-i)=" << starter.at(last-i) << std::endl;
    }
    
}

void
GeneticTSP::MutationSwapBlock(std::vector<int>& starter){
    int bsize = m_rnd.Rannyu(1.,(starter.size()-1)/2);

    int tmp;
    for(int i=starter.size()/2-bsize;i<starter.size()/2;++i){
        tmp= starter.at(i);
        starter.at(i) = starter.at(i+bsize);
        starter.at(bsize+i) = tmp;
    }
      
}

////////////////////////////////////////////////////
/////////CROSSOVER AND CROSSOVER SELECTION /////////
////////////////////////////////////////////////////
void GeneticTSP::Crossover(std::vector<int>& p1, std::vector<int>& p2){

    std::vector<int> son1, son2;

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

std::vector<int>
GeneticTSP::Select() {
    //supposedly max & min are already calculated (automatically happens when a new generation or the first gen is made).

    
    double pexp = 2.;
    int random_index;
    
    double cost, prob, r=m_rnd.Rannyu();
    do{
        random_index = (int)m_rnd.Rannyu(0.,m_population.size());
        cost = L2cost(m_population.at(random_index) );
        prob = pow((cost-m_max_cost)/(m_min_cost-m_max_cost),pexp);

    }while(r>prob);

    /*
    double prob;
    double r;
    do{
        r = m_rnd.Rannyu();
        random_index = (int)(r*m_population.size());
        prob = (pow(1-r,pexp));
        //std::cout << " r = " << r << " prob = " << prob << " random_index = " << random_index << std::endl;
    }while(m_rnd.Rannyu()>prob);
    //std::cout << "\naccepted\n";*/

return m_population.at(random_index);
    
}


///////////////////////////////////////////////////
/////////////////UTILITIES/////////////////////////
///////////////////////////////////////////////////

double
GeneticTSP::BestHalfCost(){
    double appo = 0;
    for(int i=0; i<m_population.size()/2; ++i)
        appo += L2cost(m_population.at(i));
    
    return appo*2/m_population.size();
}

void
TSP::WriteCities(const char* filename){
    std::ofstream out(filename);
    if(!out.good()){
        std::cerr << "error in opening " << filename << " to write out cities.\n";
        return;
    }

    for(auto it=m_cities.begin(); it!=m_cities.end(); ++it)
        out << (*it).GetX() << " " << (*it).GetY() << std::endl;

    out.close();
}

void
TSP::PrintPerm(std::vector<int> p){
    for(auto it=p.begin(); it!=p.end();++it)
        std::cout << *it << " ";
    std::cout << L2cost(p) << std::endl;

return;
}

void
GeneticTSP::PrintPopulation(){
    for(auto it=m_population.begin();it!=m_population.end(); ++it)
        PrintPerm(*it);
}
#endif /*TSP_H*/