//testing if a relationship between accetance and delta exists

#include <fstream>

#include "Metropolis.h"
#include "FunzioniScalari.h"

int main() {

    std::ofstream out("acceptance-delta.dat");
    expo ep;
    
    position start100(3./2.,0.,0.),
             start210(0.,0.,-5.); //starting point in a0 units
    Psi_100 * Ground = new Psi_100(1);
    Psi_210 * First  = new Psi_210(1);

    Prodotto *G = new Prodotto(Ground,Ground); //|psi^2|
    Prodotto *F = new Prodotto(First,First);   //   "

    Metropolis3D Uni100(start100,G,2.5);
    Metropolis3D Uni210(start210,F,4.0);
    Metropolis3D Gau100(start100,G,1.5);
    Metropolis3D Gau210(start210,F,2.5);
    Metropolis3D exp(start100,&ep,1.);

    double delta =0.01;



    for(int i=0; i<400; ++i){
        delta +=0.01;
        exp.SetDelta(delta);
        Uni100.SetDelta(delta);
        Uni210.SetDelta(delta);
        Gau100.SetDelta(delta);
        Gau210.SetDelta(delta);
        out << delta << " " << exp.UmeanAcceptance() << " " << exp.GmeanAcceptance()
            << " " << Uni100.UmeanAcceptance() << " " << Gau100.GmeanAcceptance()
            << " " << Uni210.UmeanAcceptance() << " " << Gau210.GmeanAcceptance() << std::endl;

    }

    out.close();

return 0;
}