//main code for execise 5 LSN
//sampling quantum hydrogen atom probability densities
//implementing Metropolis algorithm
//
//author : gilberto.nardi@studenti.unimi.it
//date: Apr 21, 2021
//
////////////////////////////////////////////////////////

#include <iostream>     //std::cout
#include <fstream>      //std::ofstream

#include "DataBlocks.h" //class DataBlocks
#include "Metropolis.h" //class Metropolis

#include "FunzioniScalari.h" //classes representing scalar multivariable funcitons (Psi_100, Psi_210, Prodotto)

int main(){

    position start100(3./2.,0.,0.),
             start210(0.,0.,-5.); //starting point in a0 units
    Psi_100 * Ground = new Psi_100(1);
    Psi_210 * First  = new Psi_210(1);

    Prodotto *G = new Prodotto(Ground,Ground); //|psi^2|
    Prodotto *F = new Prodotto(First,First);   //   "

    Metropolis3D Uni100(start100,G,1.);
    Metropolis3D Uni210(start210,F,1.);
    Metropolis3D Gau100(start100,G,1.);
    Metropolis3D Gau210(start210,F,1.);

    std::ofstream out100("output/Upoints100.dat"),
                  out210("output/Upoints210.dat");

    int B = 100,   //number of blocks
        N = 10000, //blocks size
        M = B*N;   //total throws

    //autosetting delta
    std::cout << "autosetting delta...\n";
    Uni100.UAutoSetDelta();
    Uni210.UAutoSetDelta();
    Gau100.GAutoSetDelta();
    Gau210.GAutoSetDelta();

    std::cout << " - uniform distribution - \n"
              << " ground state : delta = " << Uni100.GetDelta() << ", mean acceptance = " << Uni100.UmeanAcceptance() << std::endl
              << "  first state : delta = " << Uni210.GetDelta() << ", mean acceptance = " << Uni210.UmeanAcceptance() << std::endl
              << " - gaussian distribution - \n"
              << " ground state : delta = " << Gau100.GetDelta() << ", mean acceptance = " << Gau100.GmeanAcceptance() << std::endl
              << "  first state : delta = " << Gau210.GetDelta() << ", mean acceptance = " << Gau210.GmeanAcceptance() << std::endl;
    
    std::cout << std::endl;

    //calculating <r>

    //with proposed uniform distribution
    DataBlockingTool Ur100("output/Umean_r_100.dat",N), //tools that automatically deals with 
                     Ur210("output/Umean_r_210.dat",N); //blocking averages

    std::cout << "Metropolis with uniform proposed distribution:\n";
    for(int i=0; i<M; ++i) {
        Uni100.UIter();
        Uni210.UIter();

        double x = Uni100.GetX(),
               y = Uni100.GetY(),
               z = Uni100.GetZ();
        Ur100.AppendValue(sqrt(x*x+y*y+z*z));
        if(i%100==0) out100 << x << " " << y << " " << z << std::endl;

        x = Uni210.GetX();
        y = Uni210.GetY();
        z = Uni210.GetZ();
        Ur210.AppendValue(sqrt(x*x+y*y+z*z));
        if(i%100==0) out210 << x << " " << y << " " << z << std::endl;

        if(i%(M/10)==0) std::cout << ">step " << i << " done.\n";
    } 

    out100.close();
    out210.close();

    //with proposed Gaussian distribution

    DataBlockingTool Gr100("output/Gmean_r_100.dat",N),
                     Gr210("output/Gmean_r_210.dat",N);
    std::cout << "\nMetropolis with gaussian proposed distribution:\n";

    for(int i=0; i<M; ++i) {
        Gau100.GIter();
        Gau210.GIter();

        double x = Gau100.GetX(),
               y = Gau100.GetY(),
               z = Gau100.GetZ();
        Gr100.AppendValue(sqrt(x*x+y*y+z*z));

        x = Gau210.GetX();
        y = Gau210.GetY();
        z = Gau210.GetZ();
        Gr210.AppendValue(sqrt(x*x+y*y+z*z));

        if(i%(M/10)==0) std::cout << ">step " << i << " done.\n";
    } 

    delete G;
    delete F;
    delete Ground;
    delete First;
    return 0;
}