/****************************************************************

esercizio 2: test Teorema Limite Centrale

author: gilberto.nardi@studenti.unimi.it
date:   Mar 19th, 2021

Questioni: il dado normale in realtà da per ora  [0,1] e non val
           ori discreti!

****************************************************************/

#include <fstream>
#include "random.h"
#include <vector>

int main() {

	int iterations = 10000;                //histogram size
	std::vector<int> N = {1,2,10,100};     //different values for N
	
	Random rnd;
	rnd.Initialize();
	
	//normal dice
	std::ofstream outNorm("data/2norm.dat");
		
	for(int i=0; i<iterations; ++i) {
		for(auto it = N.begin(); it!=N.end(); ++it){
		double sum=0;
			for(int j=0; j<*it; ++j){
				int roll=1+(int)(rnd.Rannyu(0,6));
				sum+=roll;				
			}
				
			if(outNorm.good()) 
				outNorm << sum/static_cast<double>(*it) << " ";
		}
			 
	if(outNorm.good())      	 //output format : N =  1   2   10   100
		outNorm << std::endl;    //                    xxx xxx xxxx  xxxx                                     
	}
	
	outNorm.close();
	
	//"exponential" dice
	std::ofstream outExp("data/2exp.dat");
		
	for(int i=0; i<iterations; ++i) {
		for(auto it = N.begin(); it!=N.end(); ++it){
		double sum=0;
			for(int j=0; j<*it; ++j)
				sum+=rnd.Expo(1);
				
			if(outExp.good()) 
				outExp << sum/static_cast<double>(*it) << " ";
		}
	if(outExp.good())         //output format : N =  1   2   10   100
		outExp << std::endl;  //                    xxx xxx xxxx  xxxx
	}	                                      
	
	outExp.close();
	
	//"Lorentz" dice
	std::ofstream outLor("data/2lor.dat");
		
	for(int i=0; i<iterations; ++i) {
		for(auto it = N.begin(); it!=N.end(); ++it){
		double sum=0;
			for(int j=0; j<*it; ++j)
				sum+=rnd.Cauchy(1);
				
			if(outLor.good()) 
				outLor << sum/static_cast<double>(*it) << " ";
		}
	if(outLor.good())         //output format : N =  1   2   10   100
		outLor << std::endl;  //                    xxx xxx xxxx  xxxx
	}	                                      
	
	outLor.close();
	rnd.SaveSeed();

return 0;
}
