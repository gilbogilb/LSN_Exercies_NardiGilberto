//code created to test the selection operator implemented in TSP.h
//author: gilberto.nardi@studenti.unimi.it
//date  : May 29th, 2021

#include <iostream>
#include <fstream>

#include "tsp.h"

int main(){

    int popsize = 100,
         cities = 32;
    GeneticTSP problem(popsize,cities,'C');

    std::ofstream out("output/selection_operator/selection.dat");
    double cost,
            min = problem.GetMinCost(),
            max = problem.GetMaxCost();
    double p=2;
    std::vector<int> selected;
    std::vector<std::vector<int> > pop = problem.GetPop();
    for(int i=0; i<1000; ++i){
        selected=problem.Select();
        cost=problem.L2cost(selected);
        out << cost << " " << pow((cost-max)/(min-max),p) << std::endl;
    }
    out.close();
    return 0;
}