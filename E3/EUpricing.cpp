/****************************************************************

ESERCIZIO 3: Calcolo MonteCarlo dei prezzi di Call e Put per 
             Opzioni Europee

author : gilberto.nardi@studenti.unimi.it
date   : Apr 8th, 2020

****************************************************************/

#include <iostream>
#include <fstream>
#include <cmath>

#include "random.h"

double GBMfactor(double mu, double sigma, double DT, double Z){
    return exp((mu-sigma*sigma/2.)*DT+sigma*Z*sqrt(DT));
}

double error (double av, double av2, double N){
    if(N==0)
        return 0;
    else
        return sqrt((av2-av*av)/N);
}

int main(){


    Random rnd;
    rnd.Initialize();

    std::ofstream call("data/EUpriceCALL.dat"),
                   put("data/EUpricePUT.dat");
    
    if(!call.good()){
        std::cerr << "error in opening \"data/EUpriceCALL.dat\" file. End\n";
        return 1;
    }

    if(!put.good()){
        std::cerr << "error in opening \"data/EUpricePUT.dat\" file. End\n";
        return 1;
    }

    //simulation parameters
    int N = 100, //blocks size
        B = 100,  //blocks number
        M = B*N;  //total throws
    
    int n = 100; //number of steps when evolving S(T)
    
    //system parameters
    double S0    = 100.,
           T     = 1.,
           K     = 100.,
           r     = 0.1,
           sigma = 0.25;
    
    //containers
    double prog_meanC1 = 0, prog_meanC1_2 = 0,
           prog_meanCn = 0, prog_meanCn_2 = 0,
           prog_meanP1 = 0, prog_meanP1_2 = 0,
           prog_meanPn = 0, prog_meanPn_2 = 0;


    //actual computation - data blocking
    for(int j=0; j<B; ++j){

        double Call1 = 0,
               Calln = 0;
        
        double Put1 = 0,
               Putn = 0;

        //single block
        for(int i=0; i<N; ++i) {
            double ST1 = S0, //S(T) with a single step
                   STn = S0; //S(T) with n=100 steps
            
            ST1 = ST1*GBMfactor(r,sigma,T,rnd.Gauss(0,1));
            for(int j=0; j<n; ++j)
                STn = STn*GBMfactor(r,sigma,T/static_cast<double>(n),rnd.Gauss(0,1));

            Call1 += exp(-r*T)*std::max(0.,ST1-K);
            Calln += exp(-r*T)*std::max(0.,STn-K);
            
            Put1 += exp(-r*T)*std::max(0.,K-ST1);
            Putn += exp(-r*T)*std::max(0.,K-STn);

        }
    
    Call1/=N;
    Calln/=N;
    Put1/=N;
    Putn/=N;

    prog_meanC1 = (prog_meanC1*j + Call1)/static_cast<double>(j+1);
    prog_meanC1_2 = (prog_meanC1_2*j + Call1*Call1)/static_cast<double>(j+1);

    prog_meanP1 = (prog_meanP1*j + Put1)/static_cast<double>(j+1);
    prog_meanP1_2 = (prog_meanP1_2*j + Put1*Put1)/static_cast<double>(j+1);

    prog_meanCn = (prog_meanCn*j + Calln)/static_cast<double>(j+1);
    prog_meanCn_2 = (prog_meanCn_2*j + Calln*Calln)/static_cast<double>(j+1);

    prog_meanPn = (prog_meanPn*j + Putn)/static_cast<double>(j+1);
    prog_meanPn_2 = (prog_meanPn_2*j + Putn*Putn)/static_cast<double>(j+1);

    call << prog_meanC1 << " " << error(prog_meanC1,prog_meanC1_2,j) << " " << prog_meanCn << " " << error(prog_meanCn,prog_meanCn_2,j) << std::endl;
    put  << prog_meanP1 << " " << error(prog_meanP1,prog_meanP1_2,j) << " " << prog_meanPn << " " << error(prog_meanPn,prog_meanPn_2,j) << std::endl;

    }

    std::cout << "final: Call1 = " << prog_meanC1 << " +- " << error(prog_meanC1,prog_meanC1_2,B-1) << std::endl
              << "        Put1 = " << prog_meanP1 << " +- " << error(prog_meanP1,prog_meanP1_2,B-1) << std::endl
              << "       Calln = " << prog_meanCn << " +- " << error(prog_meanCn,prog_meanCn_2,B-1) << std::endl
              << "        Putn = " << prog_meanPn << " +- " << error(prog_meanPn,prog_meanPn_2,B-1) << std::endl;

    call.close();
    put.close();

return 0;
}