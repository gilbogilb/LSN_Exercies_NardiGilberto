//header file to define classes representing scalar functions
//in a multidimensional variable

//gilberto.nardi@studenti.unimi.it
//apr 23rd, 2021

#ifndef FUNZIONI_SCALARI_H
#define FUNZIONI_SCALARI_H

#include <cmath>

class FunzioneScalare3{

  public:

    virtual double Eval(double x, double y, double z) const = 0;

};


class Psi_100 : public FunzioneScalare3 {

  public:
    Psi_100(double a0): m_a0(a0) {} ;
    ~Psi_100(){};

    double Eval(double x, double y, double z) const {return pow(m_a0,-3/2)/sqrt(M_PI)*exp(-sqrt(x*x+y*y+z*z)/m_a0);};
  
  private:
    double m_a0; //makes it more comfortable to swtich between SI units and 'natural' (a0) units

};

class Psi_210 : public FunzioneScalare3 {

  public:
    Psi_210(double a0): m_a0(a0) {};
    ~Psi_210(){};

    double Eval(double x, double y, double z) const {return (pow(m_a0,5./2.)/8.) * sqrt(2./M_PI) * exp(-sqrt(x*x+y*y+z*z)/(2*m_a0)) * z; };

  private:
    double m_a0;


};

class Prodotto: public FunzioneScalare3{

  public:
    Prodotto(): m_f1(NULL), m_f2(NULL){};
    Prodotto(FunzioneScalare3 *f1, FunzioneScalare3 *f2): m_f1(f1), m_f2(f2) {};
    ~Prodotto(){};

    double Eval(double x, double y, double z) const{return m_f1->Eval(x,y,z)*m_f2->Eval(x,y,z);}

    bool IsGood() {if (m_f1==NULL || m_f2==NULL) {return false;} else{return true;}} //checks if the pointers are NULL

  private:
    FunzioneScalare3 *m_f1, *m_f2;

};

class expo : public FunzioneScalare3 {

  public:
    expo(){};
    ~expo(){};
    double Eval(double x, double y, double z) const {return exp(-sqrt(x*x+y*y*z*z));}

};

#endif /*FUNZIONI_SCALARI_H*/