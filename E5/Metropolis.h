//class to implement Metropolis algorithm
//
//autohr: gilberto.nardi@studenti.unimi.it
//date :  Apr 21, 2021

#ifndef METROPOLIS_H
#define METROPOLIS_H

#include <algorithm>
#include <iostream>

#include "random.h"
#include "FunzioniScalari.h"

class position {

	public:
		position(double x, double y, double z): m_x(x), m_y(y), m_z(z) {};
		position(): m_x(0), m_y(0), m_z(0) {};
        position(const position& p): m_x(p.GetX()), m_y(p.GetY()), m_z(p.GetZ()) {};
		~position(){};
		
		double distance (position& p) const {return sqrt(pow(m_x-p.GetX(),2) + pow(m_y-p.GetY(),2) + pow(m_z-p.GetZ(),2));};
		
		double GetX() const {return m_x;};
		double GetY() const {return m_y;};
		double GetZ() const {return m_z;};
		
		void SetX(double x) {m_x=x;};
		void SetY(double y) {m_y=y;};
		void SetZ(double z) {m_z=z;};
		
	protected:
	
		double m_x, m_y, m_z;

};

class Metropolis3D : public position{

    public:
        Metropolis3D(position start, FunzioneScalare3 *probability, double delta);
        ~Metropolis3D();

        void UIter(); //with proposed uniform probability
        void UAutoSetDelta();
        double UmeanAcceptance();

        void GIter(); //with proposed gaussian probability
        void GAutoSetDelta();
        double GmeanAcceptance();

        double GetDelta() const {return m_delta;};
        void SetDelta(double d) {m_delta=d;}

    private:
        Random m_rnd;
        double m_delta;
        FunzioneScalare3 *m_prob;

};

Metropolis3D::Metropolis3D(position start, FunzioneScalare3 *probability, double delta):
    position(start),
    m_prob(probability),
    m_delta(delta) {
        m_rnd.Initialize();
}

Metropolis3D::~Metropolis3D(){
    m_rnd.SaveSeed();
}

void
Metropolis3D::UIter(){
    double xprop = m_rnd.Rannyu(m_x-m_delta,m_x+m_delta),
           yprop = m_rnd.Rannyu(m_y-m_delta,m_y+m_delta),
           zprop = m_rnd.Rannyu(m_z-m_delta,m_z+m_delta);
    
    double alpha = std::min(1.,m_prob->Eval(xprop,yprop,zprop)/m_prob->Eval(m_x,m_y,m_z));
    
    double r = m_rnd.Rannyu();
    
    if(r<alpha) {
        m_x = xprop;
        m_y = yprop;
        m_z = zprop;
    }

}

void
Metropolis3D::GIter(){
    double xprop = m_rnd.Gauss(m_x,m_delta),
           yprop = m_rnd.Gauss(m_y,m_delta),
           zprop = m_rnd.Gauss(m_z,m_delta);
    
    double alpha = std::min(1.,m_prob->Eval(xprop,yprop,zprop)/m_prob->Eval(m_x,m_y,m_z));
    
    double r = m_rnd.Rannyu();
    
    if(r<alpha) {
        m_x = xprop;
        m_y = yprop;
        m_z = zprop;
    }

}

double
Metropolis3D::UmeanAcceptance(){
    
    position start(m_x,m_y,m_z);
    double alpha = 0, sum_alpha=0;
    int N=2000;
    for(int i=0; i<N; ++i){
        double xprop = m_rnd.Rannyu(m_x-m_delta,m_x+m_delta),
               yprop = m_rnd.Rannyu(m_y-m_delta,m_y+m_delta),
               zprop = m_rnd.Rannyu(m_z-m_delta,m_z+m_delta);

        alpha = std::min(1.,m_prob->Eval(xprop,yprop,zprop)/m_prob->Eval(m_x,m_y,m_z));
        sum_alpha += alpha;
        double r = m_rnd.Rannyu();
    
        if(r<alpha) {
            m_x = xprop;
            m_y = yprop;
            m_z = zprop;
        }
    }

    //back to the original position
    m_x=start.GetX();
    m_y=start.GetY();
    m_z=start.GetZ();

    return sum_alpha/(double)N;
}

double
Metropolis3D::GmeanAcceptance(){
    double alpha = 0, sum_alpha=0.;
    position start(m_x,m_y,m_z);
    int N=2000;
    for(int i=0; i<N; ++i){
        double xprop = m_rnd.Gauss(m_x,m_delta),
               yprop = m_rnd.Gauss(m_y,m_delta),
               zprop = m_rnd.Gauss(m_z,m_delta);
        alpha = std::min(1.,m_prob->Eval(xprop,yprop,zprop)/m_prob->Eval(m_x,m_y,m_z));
        sum_alpha += alpha;
        double r = m_rnd.Rannyu();
    
        if(r<alpha) {
            m_x = xprop;
            m_y = yprop;
            m_z = zprop;
        }
    }

    //back to the original position
    m_x=start.GetX();
    m_y=start.GetY();
    m_z=start.GetZ();

    return sum_alpha/(double)N;
}

void
Metropolis3D::UAutoSetDelta(){

    double alpha;
    do {    

    alpha = UmeanAcceptance();

    if(alpha>0.55) m_delta*=1.1;
    if(alpha<0.45) m_delta/=1.1;

    
    } while(alpha<0.45 || alpha>0.55);

}

void
Metropolis3D::GAutoSetDelta(){

    double alpha;
    do {    

    alpha = GmeanAcceptance();

    if(alpha>0.55) m_delta*=1.1;
    if(alpha<0.45) m_delta/=1.1;

    } while(alpha<0.45 || alpha>0.55);

}


#endif /*METROPOLIS_H*/