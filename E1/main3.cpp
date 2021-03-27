/****************************************************************

Buffon's experiment simulation: calculation of Pi

author: gilberto.nardi@studenti.unimi.it
date:   Mar 21st, 2021

//qualcosa non va. sembra prorio che i numeri che sputa fuori siano brutti
//il framework dovrebbe funzionare. che fare?

****************************************************************/

#include <fstream>
#include <iostream>
#include <cmath>

#include <vector>

#include "random.h"

double err(double av, double av2, int n) {

	if(n==1)
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
	rnd.Initialize("Primes","seed.in");
	
	//system parameters
	double L = 0.05;     //needle's length
	double d = 0.1;      //distnce between the lines
	
	//simulation parameters & utilities
	int B = 1e2;                   //number of blocks
	int N = 1e4;                   //block size
	int NHit=0;            //hit and total counter
	
	double progressive_mean=0;
	double progressive_square_mean=0;
	
	std::vector<double> pi,pi2;
	
	std::ofstream out("data/03.dat");
		
	for(int k=0; k<B; ++k) {   //block by block iteration
	
		NHit=0;
		
		//core - block calc
		for(int i=0; i<N; ++i){			

			// CON PI
		  double y0    = rnd.Rannyu(0,d),
				     theta = rnd.Rannyu(0,2*M_PI);
			
			double y1    = y0+L*sin(theta);
			
			// SENZA PI
			/*double x0 = rnd.Rannyu(),
			       y0 = rnd.Rannyu(0,d);
			
			double x, y;
			
			//angle generation - accept-reject
			do {
				x = rnd.Rannyu(x0-1,x0+1);
				y = rnd.Rannyu(y0-1,y0+1);
			} while( pow( x-x0,2 ) + pow( y-y0,2 ) > 1 );
			
			//double y1 = y0 + L*y/sqrt(x*x+y*y); //=y0 + L*sin(theta)
			double y1 = y0 + L*sin(atan(y/x) );
			*/
			
			//conditional statement
			if( y1>d || y1<0 )
				++NHit;
		
		}
		
		pi.push_back(2*L*N/(d*NHit) );
		pi2.push_back(pi.at(k)*pi.at(k) );
		
		progressive_square_mean=(k*progressive_square_mean+pow(2*L*N/(NHit*d),2))/static_cast<double>(k+1);
		progressive_mean=(k*progressive_mean+2*L*N/(NHit*d))/static_cast<double>(k+1);

		std::cout << sqrt( (mean(pi2)-mean(pi)*mean(pi))/((double)(k+1)) ) << " vs " << err(progressive_mean,progressive_square_mean,k+1) << std::endl;
		if(out.good()) 
			out << progressive_mean << " " << err(progressive_mean,progressive_square_mean,k+1) << std::endl;
		
	}
	
	//modo pedante
	/*double sum=0, sum2=0;
	for(int i=0; i<B; ++i) {
		sum+=pi.at(i);
		sum2+=pi2.at(i);
		std::cout << "pi: " << sum/((double)(i+1)) << " pm " << err(sum/((double)(i+1)),sum2/((double)(i+1)),i+1) << std::endl;
	}	*/	
	
	std::cout << "pi value: " << mean(pi) << " piuomeno " << err(progressive_mean,progressive_square_mean,B) << std::endl;

return 0;
}
