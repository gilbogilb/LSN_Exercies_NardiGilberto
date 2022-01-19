#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

#include "tsp.h"

int main(int argc, char *argv[]){

    int cities      = 32,
        popsize     = 1000,
        generations = 1500;
    
    if(argc!=5){
        std::cout << "Usage: ./main pc pm1 pm2 pm3\n";
        return 0;
    }
    
    double pc = std::atof(argv[1]), //crossover and mutation probabilities
          pm1 = std::atof(argv[2]),
          pm2 = std::atof(argv[3]),
          pm3 = std::atof(argv[4]);

    
    GeneticTSP problem(popsize,cities,'S'); //'C' cities on a circumference - 'S' cities in a square
    std::ofstream out("output/lowest.dat"), out50("output/lowerhalf.dat");

    //developing the generations and analyzing the costs
    for(int i=0; i<generations; ++i){
        problem.MakeGeneration(pc,pm1,pm2,pm3);
        out50 << problem.BestHalfCost() << std::endl;
        out << problem.GetMinCost() << std::endl;
        if(i%50 == 0) std::cout << "made " << i << " generations\n";
    }
    out.close();
    out50.close();

    //writing the best path
    out.open("output/bestpath.dat");
    std::vector<point2D> cities_v = problem.GetCities();
    std::vector<std::vector<int>> pop = problem.GetPop();
    for(auto it = pop.at(0).begin(); it!=pop.at(0).end(); ++it)
        out << cities_v.at(*it).GetX() << " " << cities_v.at(*it).GetY() << std::endl;

    out.close();
    return 0;
}



//utilities - functions to print vectors or vectors of vectors
void PrintPop(std::vector<std::vector<int> >& pop){
    for(auto it=pop.begin();it!=pop.end();++it){
        for(auto it2=(*it).begin();it2!=(*it).end(); ++it2)
            std::cout << *it2 << " ";
        std::cout << std::endl;
    }
}

void PrintVector(std::vector<int>& v){
    for(auto it=v.begin(); it!=v.end(); ++it) std::cout << *it << " ";
}
