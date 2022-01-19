/*********

header for classes for Random Walk simulations
author: gilberto.nardi@studenti.unimi.it
date  : March 2021

*********/

#ifndef RW_H
#define RW_H

#include "random.h"
#include <cmath>

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
		void evolveContUniform(point& p);  //evolve the position in R3 (continuum)
		
	private:
	
		Random rnd;
		double m_a; //RW step

};

RW::RW(double a): m_a(a) {
	rnd.Initialize();
}

RW::~RW(){
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

#endif /*RW_H*/
