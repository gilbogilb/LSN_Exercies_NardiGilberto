/****************************************************************

Buffon's experiment simulation: calculation of Pi

author: gilberto.nardi@studenti.unimi.it
date:   Mar 21st, 2021

****************************************************************/

#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>

#include "random.h"

double err(double av, double av2, int n) {

	if(n==0)
		return 0;
	else
		return sqrt((av2- av*av)/n);
}

double mean (std::vector<double> v) {
	double accu=0;
	for(auto it=v.begin(); it!=v.end(); ++it)
		accu+=*it;
return accu/((double)v.size());
}

	
int main() {

	Random rnd;
	rnd.Initialize();
	
	//system parameters
	double L = 0.05;     //needle's length
	double d = 0.1;      //distnce between the lines
	
	//simulation parameters & utilities
	int B    = 1e2,               //number of blocks
	    N    = 1e4,               //block size
	    NHit = 0;                 //hit counters
	
	double prog_mean=0, prog_mean2=0;
	
	std::ofstream out("data/buffon.dat");
		
	for(int k=0; k<B; ++k) {   //block by block iteration
	
		NHit=0;
		
		//core - block calc
		for(int i=0; i<N; ++i){			

			// WITH PI
		  /*double y0    = rnd.Rannyu(0,d),
				     theta = rnd.Rannyu(0,2*M_PI);
			
			double y1    = y0+L*sin(theta);
			*/
			// WITHOUT PI
			double x0 = rnd.Rannyu(),
			       y0 = rnd.Rannyu(0,d);
			
			double x, y;
			
			//angle generation - accept-reject
			do {
				x = rnd.Rannyu(x0-1,x0+1);
				y = rnd.Rannyu(y0-1,y0+1);
			} while( pow( x-x0,2 ) + pow( y-y0,2 ) > 1 );
			
			double y1 = y0 + L*(y-y0)/sqrt(pow(x-x0,2)+pow(y-y0,2)); //=y0 + L*sin(theta)

			if( y1>d || y1<0 )
				++NHit;
		
		}
		
		double pi = 2*L*N/(d*NHit);
		
		prog_mean  = (prog_mean*k+pi)/(k+1);
		prog_mean2 = (prog_mean2*k+pi*pi)/(k+1);
		
		if(out.good()) 
			out << prog_mean << " " << err(prog_mean,prog_mean2,k) << std::endl;
		
	}
	
	out.close();
    rnd.SaveSeed();
	
return 0;
}
