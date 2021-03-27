/****************************************************************

Buffon's experiment simulation: calculation of Pi

author: gilberto.nardi@studenti.unimi.it
date:   Mar 21st, 2021

Questione: probabilmente la sovrastima che si ottiene è dovuta 
alla riga extra contata o non contata al bordo. Circa risolto prendendo
tante righe

****************************************************************/

#include <fstream>
#include <iostream>
#include <cfloat>
#include <cmath>
#include <vector>

#include "random.h"

double stdDevMean(std::vector<double> v) {

	if(v.size()==1) return 0;
	
	double accu=0;
	for(auto it=v.begin(); it!=v.end(); ++it)
		accu+=*it;
		
	double mean = accu/static_cast<double>(v.size());
	double stdaccu=0;
	for(auto it=v.begin(); it!=v.end(); ++it)
		stdaccu+=(*it-mean)*(*it-mean);
	return sqrt(stdaccu/(v.size()*(v.size()-1)));
}


int main() {

	Random rnd;
	rnd.Initialize("Primes","seed.in");
	
	//system parameters
	double L = 0.05;     //needle's length
	double d = 0.1;      //distnce between the lines
	
	//simulation parameters & utilities
	int M = 1e5;                   //total throws
	int N = 1e3;                   //block size
	int B = M/N;                   //number of blocks
	int NHit=0, NTot=0;            //hit and total counter
	std::vector<double> pi, err;   //result vectors
	
	double progressive_mean=0;
	
	std::ofstream out("data/03.dat");
	
		
	for(int k=0; k<B; ++k) {   //block by block iteration
	
		NHit=0;
		NTot=0;
		
		//core - block calc
		for(int i=0; i<N; ++i) {
		
			/*  SENZA PI
			//numbers generation
			double x0 = rnd.Rannyu(0,paper),
				     y0 = rnd.Rannyu(0,paper);                    //extreme of the needle
			double tan_theta = acos( exp( -rnd.Rannyu() ) );  //distributed as tan(x) with x uniform
			
			double a = 1+tan_theta,
			       b = 2*(x0-x0*tan_theta+y0*tan_theta),
			       c = x0*x0 + y0*y0 - 2*x0*y0*tan_theta - L*L;
			       //ax^2+bx+c = 0
			
			double x1 = -b/2. + pow(-1,i)*sqrt(b*b/4. - a*c),
			       y1 = (x1-x0)*tan_theta + y0;
			*/
			
			// CON PI 
			//double /*x0    = rnd.Rannyu(0,paper),*/
		  /*		     y0    = rnd.Rannyu(0,paper),
				     theta = rnd.Rannyu(0,2*M_PI);
			
			double y1    = y0+L*sin(theta);
			*/
			
			// SENZA PI
			double x0 = rnd.Rannyu(),
			       y0 = rnd.Rannyu(0,d);
			
			double x=4, y=4; //to ensure distance>1
			//angle generation - accept-reject
			while( pow( x-x0,2 ) + pow( y-y0,2 ) < 1 ) {
				x = rnd.Rannyu(x0-L/2.,x0+L/2.);
				y = rnd.Rannyu(y0-L/2.,y0+L/2.);
			}
			
			double y1 = y0 + L*sin(atan(y/x) );
			
			//conditional statement
				if( (y0<d && d<y1) || (y1<d && d<y0) || y0*y1<0 )
					++NHit;

			++NTot;		
		}	

		progressive_mean=((k*progressive_mean+2*L*NTot/(NHit*d) )/static_cast<double>(k+1) );
		pi.push_back( progressive_mean );
		err.push_back(stdDevMean(pi) );
		
		if(out.good()) 
			out << progressive_mean << " " << stdDevMean(pi) << std::endl;
		std::cout << "bloque" << std::endl;
	}
	
	std::cout << "pi value: " << pi.at(pi.size()-1) << " piuomeno " << err.at(err.size()-1) <<  std::endl;

return 0;
}
