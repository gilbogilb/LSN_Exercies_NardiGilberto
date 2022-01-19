//main code for TSP analysis with Simulated Annealing approach
//
//author: gilberto.nardi@studenti.unimi.it
//  date: June 3rd, 2021
//
///////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>

#include "random.h"
#include "tsp.h"

int main(){
    
    int steps  = 300;

    double T0 = 7.5, dT = 0.0002, T=T0; 
    int cities=32;
    int iprint=0;

    SimulatedAnnealingTSP problem(cities,T0,'S',"seed.in");
    std::ofstream out("square/evolution0.dat");
    std::vector<int> solution;

    problem.Propose();

    while(T>0){
        ++iprint;
        problem.SetT(T);
        for(int j=0; j<steps; ++j)
            problem.Propose();
        solution = problem.GetSolution();
        if(iprint%1000==0) std::cout << "T = " << T << " beta = " << problem.GetBeta() << " cost = " << problem.L2cost(solution) << std::endl;
        out << T << " " << problem.L2cost(solution) << std::endl;
        T-=dT;
    }
    
    out.close();

    //writing the best path
    out.open("square/bestpath0.dat");
    std::vector<point2D> cities_v = problem.GetCities();
    for(auto it = solution.begin(); it!=solution.end(); ++it)
        out << cities_v.at(*it).GetX() << " " << cities_v.at(*it).GetY() << std::endl;

    
    return 0;
}