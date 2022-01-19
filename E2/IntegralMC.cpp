#include "IntegralMC.h"
#include "Funzioni.h"

#include <cmath>

IntegralMC::IntegralMC(){
	rnd.Initialize();
}

IntegralMC::~IntegralMC(){
	rnd.SaveSeed();
}

double 
IntegralMC::IntegralHoM(double xmin, double xmax, double fmax, FunzioneBase *f, int punti) {

  double x=0, y=0;
  unsigned int Nhit=0;
  for(int i=0; i<punti; ++i) {
    x=rnd.Rannyu(xmin,xmax);
    y=rnd.Rannyu(0,fmax);       //watch out for f<0!
    if(y<f->Eval(x)) ++Nhit;
  }

  return (xmax-xmin)*fmax*static_cast<double>(Nhit)/static_cast<double>(punti);
}


double 
IntegralMC::IntegralAVE(double xmin, double xmax, FunzioneBase *f, int punti) {
  double integral = 0;
  for(int i=0; i<punti; ++i) {
    integral+=f->Eval(rnd.Rannyu(xmin,xmax));
  }

  return (xmax-xmin)*integral/static_cast<double>(punti);
}

double IntegralMC::IntegralAVE(double xmin, double xmax, FunzioneBase *f, FunzioneBase *revCumulative, int punti){
	double integral = 0;
	for(int i=0; i<punti; ++i)
		integral+=f->Eval(revCumulative->Eval(rnd.Rannyu(xmin,xmax)));
	
  return (xmax-xmin)*integral/static_cast<double>(punti);
}

double 
IntegralMC::IntegralAVERej(double xmin, double xmax, FunzioneBase *f, FunzioneBase *pdf, double pdfmax, int punti){
	double integral = 0;
	double x, y;
	for(int i=0; i<punti; ++i){
		do {
			x=rnd.Rannyu(xmin,xmax);
			y=rnd.Rannyu(0,pdfmax);
		} while (pdf->Eval(x)<y);
		integral+=f->Eval(x);
	} 
return (xmax-xmin)*integral/static_cast<double>(punti);  
}
