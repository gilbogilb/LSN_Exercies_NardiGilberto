/**

author: gilberto.nardi@studenti.unimi.it
date: Mar 25th, 2020

Random Walks simulations

nota: si può mettere friend il metodo evolve. ppiù carino

**/

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>

#include "random.h"

class point {

	public:
		point(double x, double y, double z): m_x(x), m_y(y), m_z(z) {};
		point(): m_x(0), m_y(0), m_z(0) {};
		~point(){};
		
		double distance (point& p) const {return sqrt(pow(m_x-p.GetX(),2) + pow(m_y-p.GetY(),2) + pow(m_z-p.GetZ(),2));};
		
		double GetX() const {return m_x;};
		double GetY() const {return m_y;};
		double GetZ() const {return m_z;};
		
		void SetX(double x) {m_x=x;};
		void SetY(double y) {m_y=y;};
		void SetZ(double z) {m_z=z;};
		
	private:
	
		double m_x, m_y, m_z;

};

class RW {

	public:
	
		RW(double a);
		~RW();
		
		void evolveDiscrUniform(point& p); //evolve the position over a discrete lattice
		void evolveContUniform(point& p);  //evolve the position in R3
		
	private:
	
		Random rnd;
		double m_a; //RW step

};

RW::RW(double a) {
	rnd.Initialize();
	m_a=a;
}

RW::~RW(){
	rnd.SaveSeed();
}

void
RW::evolveDiscrUniform(point& p){
	int r=(int)rnd.Rannyu(0,6);
	
	switch (r) {
		case 0:
			p.SetX(p.GetX()+m_a);
			break;
		case 1:
			p.SetX(p.GetX()-m_a);
			break;
		case 2:
			p.SetY(p.GetY()+m_a);
			break;
		case 3:
			p.SetY(p.GetY()-m_a);
			break;
		case 4:
			p.SetZ(p.GetZ()+m_a);
			break;
		case 5:
			p.SetZ(p.GetZ()-m_a);
			break;
	}
	
}

void
RW::evolveContUniform(point& p){

	double theta = rnd.Rannyu(0,M_PI),
	       phi   = rnd.Rannyu(0,2*M_PI);

	p.SetX(p.GetX() + m_a*sin(theta)*cos(phi));
	p.SetY(p.GetY() + m_a*sin(theta)*sin(phi));
	p.SetZ(p.GetZ() + m_a*cos(theta));

}

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
	
	std::vector<double> norms2(steps+1,0),
	                    means(steps+1,0),
	                    means2(steps+1,0),
	                    err(steps+1,0);
	                    
	std::ofstream out("data/discreteRW.dat");
	
	
	//discrete RW
	for(int k=0; k<B; ++k) {
	
		for(auto it=norms2.begin(); it!=norms2.end(); ++it)    //Init
			*it=0;
	
		for(int j=0; j<N; ++j) {               //Block
		
			P=start;		                         //(init)		
				
			for(int i=1; i<steps+1; ++i) {       //Single Random Walk
				randomWalk.evolveDiscrUniform(P);
				norms2.at(i)+=pow(P.distance(start),2);
			}
		}
	
		for(int i=0; i<steps+1; ++i)
			norms2.at(i)/=N;
		
		for(int i=0; i<steps+1; ++i) {
			means.at(i)=( means.at(i)*k+norms2.at(i) )/((double)(k+1.) );
			means2.at(i)=( means2.at(i)*k+norms2.at(i)*norms2.at(i))/((double)(k+1.) );
		}

	}

	for(int i=2; i<steps+1; ++i) {
		err.at(i)=statisticError(means.at(i),means2.at(i),B);
	}
	
	//ora ho i valori medi e gli errori del modulo quadro. devo fare la radice!
	for(int i=0; i<steps+1; ++i){
		means.at(i) = sqrt(means.at(i));
		err.at(i)   = 1./(2*means.at(i))*err.at(i);
		if(i==0)
			err.at(i)=0;
		if(out.good())
			out << means.at(i) << " " << err.at(i) << std::endl;
	}
	
	out.close();
	out.open("data/continuousRW.dat");

	for(int i=0; i<steps+1; ++i) {
		means.at(i)  = 0;
		means2.at(i) = 0;
		err.at(i)    = 0;
	}
	//continuous RW
	for(int k=0; k<B; ++k) {
	
		for(auto it=norms2.begin(); it!=norms2.end(); ++it)    //Init
			*it=0;
	
		for(int j=0; j<N; ++j) {               //Block
		
			P=start;		                         //(init)		
				
			for(int i=1; i<steps+1; ++i) {       //Single Random Walk
				randomWalk.evolveContUniform(P);
				norms2.at(i)+=pow(P.distance(start),2);
			}
		}
	
		for(int i=0; i<steps+1; ++i)
			norms2.at(i)/=N;
		
		for(int i=0; i<steps+1; ++i) {
			means.at(i)=( means.at(i)*k+norms2.at(i) )/((double)(k+1.) );
			means2.at(i)=( means2.at(i)*k+norms2.at(i)*norms2.at(i))/((double)(k+1.) );
		}

	}

	for(int i=2; i<steps+1; ++i) {
		err.at(i)=statisticError(means.at(i),means2.at(i),B);
	}
	
	means2.clear();
	
	//ora ho i valori medi e gli errori del modulo quadro. devo fare la radice!
	for(int i=0; i<steps+1; ++i){
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
