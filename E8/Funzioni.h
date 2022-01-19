#ifndef __funzioni_h__
#define __funzioni_h__

#include <cmath>

class FunzioneBase{

  public:

    virtual double Eval(double x) const = 0;


};

class PsiTGauss : public FunzioneBase { //sum of two gaussians

  //trial wave function to find the exact wave function with quantum variational MC
  //unnormalized

  public:
    PsiTGauss(double mu, double sigma): m_sigma(sigma), m_mu(mu){};
    ~PsiTGauss(){};
    
    double Eval(double x) const {return exp( -pow( (x-m_mu)/m_sigma ,2.)/2. ) + exp( -pow( (x+m_mu)/m_sigma ,2.)/2. );};

    void SetSigma(double sigma) {m_sigma = sigma;}
    void SetMu(double mu) {m_mu = mu;}

  private:
    double m_sigma, m_mu;
};

class PsiTGaussSecond : public FunzioneBase {

  //second derivative of PsiTGauss

  public:
    PsiTGaussSecond(double mu, double sigma): m_sigma(sigma), m_mu(mu){};
    ~PsiTGaussSecond(){};
    
    double Eval(double x) const {return -( (pow((x-m_mu)/m_sigma,2.)-1)*exp(-pow((x-m_mu)/m_sigma,2.)/2.) + (pow((x+m_mu)/m_sigma,2.)-1)*exp(-pow((x+m_mu)/m_sigma,2.)/2) )/m_sigma/m_sigma;};

    void SetSigma(double sigma) {m_sigma = sigma;}
    void SetMu(double mu) {m_mu = mu;}

  private:
    double m_sigma, m_mu;
};

class HEvaluator : public FunzioneBase { //Hpsi/psi = psi''/2psi + V(x)

  //uses hbar=1, m=1

  public:
    HEvaluator(FunzioneBase *psiT, FunzioneBase *psiTsecond, FunzioneBase *potential): m_psiT(psiT), m_psiT2(psiTsecond), m_pot(potential) {};
    ~HEvaluator(){};

    double Eval(double x) const {return m_psiT2->Eval(x)/2./m_psiT->Eval(x)+m_pot->Eval(x);}
      //((pow((x-m_mu)/m_sigma,2.)-1)*exp( -pow( (x-m_mu)/m_sigma ,2.)/2. ) + (pow((x+m_mu)/m_sigma,2.)-1)*exp( -pow( (x+m_mu)/m_sigma ,2.)/2. )  )/(m_psiT.Eval(x)*m_sigma*m_sigma*-2.) + m_pot->Eval(x);}
  

  private:
    double m_mu, m_sigma;
    FunzioneBase *m_psiT, *m_psiT2;
    FunzioneBase *m_pot;

};

class DoubleHole : public FunzioneBase {

  //one type of polynomial double hole potential ( V(x)=ax^4+bx^2 )

  public:
    DoubleHole(double a, double b): m_a(a), m_b(b){}
    ~DoubleHole(){};

    double Eval(double x) const {return m_a*pow(x,4.)+m_b*pow(x,2.);};

  private:
    double m_a, m_b;

};




class Parabola: public FunzioneBase{

public:

  Parabola(): m_a(0), m_b(0), m_c(0) {};
  Parabola(double a, double b, double c): m_a(a), m_b(b), m_c(c) {};
  ~Parabola(){}; 
  double Eval(double x) const {return m_a*x*x + m_b*x + m_c;};
  void SetA(double a) {m_a = a;};
  void SetB(double b) {m_b = b;};
  void SetC(double c) {m_c = c;};
  double GetA() const {return m_a;};
  double GetB() const {return m_b;};
  double GetC() const {return m_c;};

private:

  double m_a, m_b, m_c;

};

class Seno: public FunzioneBase{

  public:

    Seno(): m_a(1), m_b(1), m_c(0) {};
    Seno(double a, double b, double c): m_a(a), m_b(b), m_c(c) {};
    ~Seno(){}; 
    double Eval(double x) const {return m_a*sin(m_b*x+m_c);};
    void SetA(double a) {m_a = a;};
    void SetB(double b) {m_b = b;};
    void SetC(double c) {m_c = c;};
    double GetA() const {return m_a;};
    double GetB() const {return m_b;};
    double GetC() const {return m_c;};

  private:
    double m_a, m_b, m_c; //parameters
} ;

class Coseno: public FunzioneBase{

  public:

    Coseno(): m_a(1), m_b(1), m_c(0) {};
    Coseno(double a, double b, double c): m_a(a), m_b(b), m_c(c) {};
    ~Coseno(){}; 
    double Eval(double x) const {return m_a*cos(m_b*x+m_c);};
    void SetA(double a) {m_a = a;};
    void SetB(double b) {m_b = b;};
    void SetC(double c) {m_c = c;};
    double GetA() const {return m_a;};
    double GetB() const {return m_b;};
    double GetC() const {return m_c;};

  private:
    double m_a, m_b, m_c; //parameters
} ;

class Radical: public FunzioneBase {

	public:
		
		Radical(): m_a(1), m_b(0), m_c(1){}; //sqrt(x)
		Radical(double a, double b, double c): m_a(a), m_b(b), m_c(c) {}; //c*sqrt(ax+b)
		~Radical(){};
		
		double Eval(double x) const {return m_c*sqrt(m_a*x+m_b);};
		
	private:
		double m_a, m_b, m_c;

};

class Constant: public FunzioneBase {

	public:
		Constant(double c): m_c(c){};
		~Constant(){};
		
		double Eval(double x) const {return m_c;};
	
	private:
		double m_c;

};

class Somma: public FunzioneBase{

  public:
    Somma(): m_f1(NULL), m_f2(NULL){};
    Somma(FunzioneBase *f1, FunzioneBase *f2): m_f1(f1), m_f2(f2) {};
    ~Somma(){};

    double Eval(double x) const{return m_f1->Eval(x)+m_f2->Eval(x);}

    bool IsGood() {(m_f1==NULL || m_f2==NULL)?false:true;} //checks if the pointers are NULL

  private:
    FunzioneBase *m_f1, *m_f2;

};

class Prodotto: public FunzioneBase{

  public:
    Prodotto(): m_f1(NULL), m_f2(NULL){};
    Prodotto(FunzioneBase *f1, FunzioneBase *f2): m_f1(f1), m_f2(f2) {};
    ~Prodotto(){};

    double Eval(double x) const{return m_f1->Eval(x)*m_f2->Eval(x);}

    bool IsGood() {(m_f1==NULL || m_f2==NULL)?false:true;} //checks if the pointers are NULL

  private:
    FunzioneBase *m_f1, *m_f2;

};

class Divisione: public FunzioneBase{

	public:
		Divisione(): m_f1(NULL), m_f2(NULL){};
		Divisione(FunzioneBase *f1, FunzioneBase *f2): m_f1(f1), m_f2(f2) {};
		~Divisione(){};
		
		double Eval(double x) const {return m_f1->Eval(x)/m_f2->Eval(x);}
		
		bool IsGood() {(m_f1==NULL || m_f2==NULL)?false:true;} //checks if the pointers are NULL

  private:
    FunzioneBase *m_f1, *m_f2;

};

#endif /*__funzioni_h__*/
