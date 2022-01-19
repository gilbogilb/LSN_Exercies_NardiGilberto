//main code for Quantum Variational MC exercises
//
//author: gilberto.nardi@studenti.unimi.it
//date: May 13th, 2021
//
//////////////////////////////////////////////////

#include <iostream>
#include <float.h> //DBL_MAX

#include "Metropolis.h"
#include "Funzioni.h"
#include "DataBlocks.h"


int main(){

    //Simulation parameters
    int M = 1E5, //total throws
        N = 1000,//blocks size
        B = M/N; //blocks number
    
    //initial numerical parameters 
    double mu    = 0.5,
           sigma = 0.2;

    //define some function objects we need for the calculations
    PsiTGauss psi(mu, sigma);  //psiT
    Prodotto psi2(&psi,&psi);    //|psi|^2
    PsiTGaussSecond psisec(mu,sigma);
    Prodotto psisec2(&psisec,&psisec);
    DoubleHole V(1.,-5./2.);     //V(x) = x^4 - 5/2*x^2

    HEvaluator H(&psi,&psisec,&V); //function to be evaluated

    //metropolis class - used to sample a given pdf (psi2)
    Metropolis1D metro(mu,&psi2,0.5);

    //iterating the calculations over a grid of mu, sigma
    int steps = 25;
    double mu_test, sigma_test;
    double integral;
    double mu_min = 0., sigma_min = 0., H_temp=DBL_MAX; //brute force: the initialization value
                                                        //for H temp is so big that the min of <H> will 
                                                        //for sure be smaller 
    std::ofstream out("output/parameters.dat");
    std::ofstream matrix("output/matrix.dat");  //<H>_{\mu,\sigma} (sigma = cols mu = rows)
    std::ofstream acc("output/acceptance.dat");

    for(int i=0; i<steps; ++i){
        mu_test = mu + (double)i/(double)steps*1.;
        for(int j = 0; j<steps; ++j){
            sigma_test = sigma + (double)j/(double)steps*1.;
            integral = 0.;  //to store the integral value


            psi.SetMu(mu_test);
            psi.SetSigma(sigma_test);
            psisec.SetMu(mu_test);
            psisec.SetSigma(sigma_test);
            metro.UAutoSetDelta();

            acc << metro.UMeanAcceptance() << " " << metro.GetDelta() << std::endl;

            for(int k = 0; k<(M/10); ++k){  //calculate <H>
                metro.UIter();
                integral+=H.Eval(metro.GetX());
            }
        
            integral/=(M/10.);
        
            matrix << integral << " ";

            //find optimizing parameters
            if(integral<H_temp){
                H_temp = integral;
                mu_min=mu_test;
                sigma_min=sigma_test;
            }
        }
        matrix << std::endl;
    }

    out.close();
    matrix.close();
    acc.close();

    //Final calculation - with minimizing values for sigma, mu
    psi.SetSigma(sigma_min);
    psi.SetMu(mu_min);
    psisec.SetSigma(sigma_min);
    psisec.SetMu(mu_min);
    metro.SetX(mu_min);
    metro.UAutoSetDelta();
    std::cout << "metro acceptance - final calculation " << metro.UMeanAcceptance() << std::endl; 

    DataBlockingTool tool("output/blocks.dat",N);
    out.open("output/psi2pdf.dat");
    for(int i=0; i<M; ++i){
        metro.UIter();
        tool.AppendValue( H.Eval(metro.GetX()) );
        out << metro.GetX() << std::endl;
    }
    out.close();
    /*out.open("output/final.dat");

    out << "\n mu = " << mu_min << ", sigma = " << sigma_min << std::endl;
    out << " <H> = " << tool.GetMean() << " +- " << tool.GetError() << std::endl;*/

    std::cout << "\n mu = " << mu_min << ", sigma = " << sigma_min << std::endl;
    std::cout << " <H> = " << tool.GetMean() << " +- " << tool.GetError() << std::endl;
    
    out.close();

return 0;
}