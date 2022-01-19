/**

author: gilberto.nardi@studenti.unimi.it
date: Mar 25th, 2020

Random Walks simulations

**/

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "RW.h"

double statisticError(double av, double av2, int N) {
	if(N==0)
		return 0;
	else
		return sqrt((av2-av*av)/((double)N));
}


int main() {

	point start(0,0,0), P;
	RW randomWalk(1);
	
	int steps = 100, //steps of evolution in the random walk
	    M     = 1e4, //total simulations
	    B     = 100, //number of blocks
	    N     = M/B; //number of elements of a block
	
	std::vector<double> norms2(steps,0.),  //constructor fills them with zeros
	                    means(steps,0.),
	                    means2(steps,0.),
	                    err(steps,0.);
	
	double prog_mean = 0, prog_mean_2 = 0;
	                    
	std::ofstream out("data/discreteRW.dat");

	out << "0 0\n";  //starting point
	
	//discrete RW
	for(int k=0; k<B; ++k) {
	
		norms2=std::vector<double>(steps,0.);

		for(int j=0; j<N; ++j) {               //Single block
		
			P=start;		                   //restart from (0,0,0)
			for(int i=0; i<steps; ++i) {       //Single Random Walk
				randomWalk.evolveDiscrUniform(P);
				norms2.at(i)+=pow(P.distance(start),2);
				if(i==0) std::cout << "j=" << j << " cumsum=" << norms2.at(i) << std::endl;
			}
		}
	
		std::cout << norms2.at(0) << " then ";
		for(int i=0; i<steps; ++i)           //renormalization
			norms2.at(i)/=N;
		std::cout << norms2.at(0) << std::endl;


		for(int i=0; i<steps; ++i) {
			means.at(i)=( means.at(i)*k+norms2.at(i) )/((double)(k+1.) );
			means2.at(i)=( means2.at(i)*k+norms2.at(i)*norms2.at(i))/((double)(k+1.) );
		}

	}

	std::cout << std::endl;

	//(final) error over the estimate of <|r|^2> as a function of the step
	for(int i=0; i<steps; ++i)
		err.at(i)=statisticError(means.at(i),means2.at(i),B-1);
	
	std::cout << "testing the first step: mean=" << means.at(0) << ", mean2=" << means2.at(0)
	          << ", err=" << statisticError(means.at(0),means2.at(0),B-1)<<std::endl;
	
	//we have calculated |r|^2 and its error. Here we calculate the square root
	for(int i=0; i<steps; ++i){

			means.at(i) = sqrt(means.at(i));
			err.at(i)   = 1./(2*means.at(i))*err.at(i);

		if(out.good())
			out << means.at(i) << " " << err.at(i) << std::endl;
	}
	
	out.close();
	out.open("data/continuousRW.dat");

	out << "0 0\n";  //starting point

	for(int i=0; i<steps; ++i) {
		norms2.at(i) = 0.;
		means.at(i)  = 0.;
		means2.at(i) = 0.;
		err.at(i)    = 0.;
	}
	//continuous RW
	for(int k=0; k<B; ++k) {

		norms2=std::vector<double>(steps,0.);
	
		for(int j=0; j<N; ++j) {               //Single block
		
			P=start;		                   //restart from (0,0,0)	
			for(int i=0; i<steps; ++i) {       //Single Random Walk
				randomWalk.evolveContUniform(P);
				norms2.at(i)+=pow(P.distance(start),2);
			}
		}
	
		for(int i=0; i<steps; ++i)           //renormalization
			norms2.at(i)/=N;
		
		for(int i=0; i<steps; ++i) {        
			means.at(i)=( means.at(i)*k+norms2.at(i) )/((double)(k+1.) );
			means2.at(i)=( means2.at(i)*k+norms2.at(i)*norms2.at(i))/((double)(k+1.) );
		}

	}

	for(int i=0; i<steps; ++i)
		err.at(i)=statisticError(means.at(i),means2.at(i),B-1);
	
	means2.clear(); //let's free some space

	for(int i=0; i<steps; ++i){
		means.at(i) = sqrt(means.at(i));
		err.at(i)   = 1./(2*means.at(i))*err.at(i);
		if(i==0)
			err.at(i)=0;
		if(out.good())
			out << means.at(i) << " " << err.at(i) << std::endl;
	}
	
	out.close();
	
return 0;
}
