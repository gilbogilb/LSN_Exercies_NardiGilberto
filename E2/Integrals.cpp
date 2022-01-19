/****************************************************************

author: gilberto.nardi@studenti.unimi.it
date:   Mar 25, 2020

Calculations of the integral int_0^1 pi/2*cos(pi*x/2)dx
(LSN exercise 2.1)

Questioni: qual è l'indice da dare alla funzione errore?

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
	
	IntegralMC Integrator;
	
	double u_progressive_mean=0,
	       u_progressive_square_mean=0,
	       imp_progressive_mean=0,
	       imp_progressive_square_mean=0;
	
	std::ofstream out("data/UnifInt.dat");
	
	if(!out.good()) {
		std::cerr << "WARNING: error opening the output file.\n";
		return -1;
	}
	
	//uniform distribution
	for(int i=0; i<B;++i) {
		double integral = Integrator.IntegralAVE(0,1,f,N);

		u_progressive_mean = (u_progressive_mean*i+integral)/static_cast<double>(i+1);
	 	u_progressive_square_mean = (u_progressive_square_mean*i+integral*integral)/static_cast<double>(i+1);
		
		if(out.good())
			out << u_progressive_mean << " " << err(u_progressive_mean, u_progressive_square_mean,i) << std::endl;
	}
	
	out.close();
	out.open("data/ImpInt.dat");
	
	//importance sampling with pdf 
	Radical * rad = new Radical(-1,1,-1); //-sqrt(1-x)
	Constant * c  = new Constant(1);
	Somma * pdfCumulative = new Somma(c,rad); //1-sqrt(1-x)
	Parabola * pdf  = new Parabola(0,-2,2); //2(1-x) (pdf)
	Divisione * integrand = new Divisione(f,pdf);
	//defining all these function is a bit sloppy and complex... 
	//but it allows to have classes that are quite adaptive and recyclable
	
	if(!out.good()) {
		std::cerr << "WARNING: error opening the output file.\n";
		return -1;
	}
	
	for(int i=0; i<B; ++i) {
		double integral = Integrator.IntegralAVE(0,1,integrand,pdfCumulative,N);
		
		imp_progressive_mean = (imp_progressive_mean*i+integral)/static_cast<double>(i+1);
		imp_progressive_square_mean = (imp_progressive_square_mean*i+integral*integral)/static_cast<double>(i+1);
	
	if(out.good())
			out << imp_progressive_mean << " " << err(imp_progressive_mean, imp_progressive_square_mean,i) << std::endl;
	
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
