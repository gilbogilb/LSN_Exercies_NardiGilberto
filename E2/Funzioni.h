#ifndef __funzioni_h__
#define __funzioni_h__

#include <cmath>

class FunzioneBase{

  public:

    virtual double Eval(double x) const = 0;

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

    bool IsGood() {if(m_f1==NULL || m_f2==NULL){return false;} else { return true;} } //checks if the pointers are NULL

  private:
    FunzioneBase *m_f1, *m_f2;

};

class Prodotto: public FunzioneBase{

  public:
    Prodotto(): m_f1(NULL), m_f2(NULL){};
    Prodotto(FunzioneBase *f1, FunzioneBase *f2): m_f1(f1), m_f2(f2) {};
    ~Prodotto(){};

    double Eval(double x) const{return m_f1->Eval(x)*m_f2->Eval(x);}

    bool IsGood() {if(m_f1==NULL || m_f2==NULL){return false;} else { return true;} } //checks if the pointers are NULL

  private:
    FunzioneBase *m_f1, *m_f2;

};

class Divisione: public FunzioneBase{

	public:
		Divisione(): m_f1(NULL), m_f2(NULL){};
		Divisione(FunzioneBase *f1, FunzioneBase *f2): m_f1(f1), m_f2(f2) {};
		~Divisione(){};
		
		double Eval(double x) const {return m_f1->Eval(x)/m_f2->Eval(x);}
		
		bool IsGood() {if(m_f1==NULL || m_f2==NULL){return false;} else { return true;} } //checks if the pointers are NULL

  private:
    FunzioneBase *m_f1, *m_f2;

};

#endif /*__funzioni_h__*/
