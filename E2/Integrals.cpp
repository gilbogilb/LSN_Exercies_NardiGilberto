/****************************************************************

author: gilberto.nardi@studenti.unimi.it
date:   Mar 25, 2020

Calculations of the integral int_0^2 pi/2*cos(pi*x/2)dx
(LSN exercise2.1)

Questini: qual è l'indice da dare alla funzione errore?

****************************************************************/

#include <iostream>
#include <fstream>

#include "IntegralMC.h"
#include "Funzioni.h"

double err(double av, double av2, int N) {
	if(N==0)
		return 0;
	else
		return sqrt((av2-av*av)/((double)N));
}

int main() {

	int M = 1e4, //total throws
	    B = 100, //number of blocks
	    N = M/B; //number of throws per block
	
	//uniform distribution
	Coseno * f = new Coseno(M_PI/2.,M_PI/2.,0); //obj representing the function to integrate
	
	//WEAK importance sampling 
	//Parabola * pdf = new Parabola(-3./2.,0,3./2.);//representing pdf 3/2(1-x^2)
	//Divisione * ARintegrand = new Divisione(f,pdf); //     "       c*cos(...)/(1-x^2)
	
	IntegralMC Integrator;
	
	double u_progressive_mean=0,
	       u_progressive_square_mean=0,
	       //ARimp_progressive_mean=0,
	       //ARimp_progressive_square_mean=0,
	       imp_progressive_mean=0,
	       imp_progressive_square_mean=0;
	
	std::ofstream out("data/UnifInt.dat");
	
	if(!out.good()) {
		std::cerr << "WARNING: error opening the output file.\n";
		return -1;
	}
	
	for(int i=0; i<B;++i) {
		double integral     = Integrator.IntegralAVE(0,1,f,N),
		       //ARimp_integral = Integrator.IntegralAVERej(0,1,ARintegrand,pdf,3./2.,N),
		       //imp_integral   = Integrator.IntegralAVE(0,1,integrand,p,N);
		       
		u_progressive_mean = (u_progressive_mean*i+integral)/static_cast<double>(i+1);
		u_progressive_square_mean = (u_progressive_square_mean*i+integral*integral)/static_cast<double>(i+1);
		
		//ARimp_progressive_mean = (ARimp_progressive_mean*i+ARimp_integral)/static_cast<double>(i+1);
		//ARimp_progressive_square_mean = (ARimp_progressive_square_mean*i+ARimp_integral*ARimp_integral)/static_cast<double>(i+1);
		
		//imp_progressive_mean = (imp_progressive_mean*i+imp_integral)/static_cast<double>(i+1);
		//imp_progressive_square_mean = (imp_progressive_square_mean*i+imp_integral*imp_integral)/static_cast<double>(i+1);		
		
		if(out.good())
			out << u_progressive_mean << " " << err(u_progressive_mean, u_progressive_square_mean,i+1) << std::endl;
			    //<< " " << ARimp_progressive_mean << " " << err(ARimp_progressive_mean, ARimp_progressive_square_mean,i+1) 
			    //<< " " << imp_progressive_mean << " " << err(imp_progressive_mean, imp_progressive_square_mean,i+1) << std::endl;
	}
	
	out.close();
	out.open("data/ImpInt.dat");
	
	//good importance sampling
	Radical * rad = new Radical(-1,1,-1); //-sqrt(1-x)
	Constant * c  = new Constant(1);
	Somma * pdfCumulative = new Somma(c,rad);
	Parabola * pdf  = new Parabola(0,-2,2); //2(1-x) (pdf)
	Divisione * integrand = new Divisione(f,pdf);
	
	if(!out.good()) {
		std::cerr << "WARNING: error opening the output file.\n";
		return -1;
	}
	
	for(int i=0; i<B; ++i) {
		double integral = Integrator.IntegralAVE(0,1,integrand,pdfCumulative,N);
		
		imp_progressive_mean = (imp_progressive_mean*i+integral)/static_cast<double>(i+1);
		imp_progressive_square_mean = (imp_progressive_square_mean*i+integral*integral)/static_cast<double>(i+1);	
	
	if(out.good())
			out << imp_progressive_mean << " " << err(imp_progressive_mean, imp_progressive_square_mean,i+1) << std::endl;
	
	}
	
	out.close();
	
	delete integrand;
	delete pdfCumulative;
	delete pdf;
	delete c;
	delete rad;
	delete f;

return 0;
}
