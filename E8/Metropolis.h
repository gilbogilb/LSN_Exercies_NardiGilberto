//class to implement Metropolis algorithm
//
//autohr: gilberto.nardi@studenti.unimi.it
//date :  Apr 21, 2021
//updated for 1D Metropolis may 13th, 2021

#ifndef METROPOLIS_H
#define METROPOLIS_H

#include <algorithm>
#include <iostream>

#include "random.h"
#include "Funzioni.h"

class Metropolis1D {

    public:
        Metropolis1D(double start, FunzioneBase *probability, double delta);
        ~Metropolis1D(){};

        void UIter();  //with uniform probability
        void GIter();  //with gaussian probability

        void UAutoSetDelta();
        double UMeanAcceptance();

        void SetX(double x) {m_x = x;}
        void SetDelta(double delta) {m_delta = delta;}

        double GetX() const {return m_x;};
        double GetDelta() const {return m_delta;};
    
    private:
        Random m_rnd;
        double m_x;
        FunzioneBase *m_prob;
        double m_delta;

};

Metropolis1D::Metropolis1D(double start, FunzioneBase *probability, double delta):
    m_x(start), m_prob(probability), m_delta(delta) {
        m_rnd.Initialize();
}

void
Metropolis1D::UIter(){

    double xprop = m_rnd.Rannyu(m_x-m_delta,m_x+m_delta);
    double alpha = std::min(1.,m_prob->Eval(xprop)/m_prob->Eval(m_x));    
    double r = m_rnd.Rannyu();
    
    if(r<alpha) m_x = xprop;
}

void 
Metropolis1D::UAutoSetDelta(){
    double alpha;
    do {    

    alpha = UMeanAcceptance();

    if(alpha>0.55) m_delta*=1.1;
    if(alpha<0.45) m_delta/=1.1;

    } while(alpha<0.45 || alpha>0.55);
}

double
Metropolis1D::UMeanAcceptance(){

    double x0 = m_x;
    double alpha = 0, sum_alpha=0;
    int N=2000;

    for(int i=0; i<N; ++i){
        double xprop = m_rnd.Rannyu(m_x-m_delta,m_x+m_delta);
        alpha = std::min(1.,m_prob->Eval(xprop)/m_prob->Eval(m_x));
	    sum_alpha +=alpha;
        double r = m_rnd.Rannyu();
    
        if(r<alpha) m_x = xprop;

    }

    //back to the initial position
    m_x=x0;

    return sum_alpha/double(N);

}

void
Metropolis1D::GIter(){

    double xprop = m_rnd.Gauss(m_x,m_delta);
    double alpha = std::min(1.,m_prob->Eval(xprop)/m_prob->Eval(m_x));    
    double r = m_rnd.Rannyu();
    
    if(r<alpha) m_x = xprop;
}




#endif /*METROPOLIS_H*/
