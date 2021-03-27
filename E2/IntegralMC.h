#ifndef INTEGRAL_MC
#define INTEGRAL_MC

#include "random.h"
#include "Funzioni.h"

//warning! it only works with positive functions

class IntegralMC {

  public:

    IntegralMC();
    ~IntegralMC();

    double IntegralHoM(double xmin, double xmax, double fmax, FunzioneBase *f, int punti);
    double IntegralAVE(double xmin, double xmax, FunzioneBase *f, int punti);
    double IntegralAVE(double xmin, double xmax, FunzioneBase *f, FunzioneBase *revCumulative, int punti);   //importance sampling with a known and invertible cumulative
    double IntegralAVERej(double xmin, double xmax, FunzioneBase *f, FunzioneBase *pdf, double pdfmax, int punti);          //importance sampling with accept-reject pdf distribution
 
  private:

    Random rnd;
};

#endif /*INTEGRAL_MC*/
