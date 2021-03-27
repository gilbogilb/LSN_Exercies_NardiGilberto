/****************************************************************

author:gilberto.nardi@studenti.unimi.it
date: Mar 18th, 2021

code to test the 'Random' class

Questione: io sto in realtà usando una sottosuccessione, mettendo
nello stesso ciclo la media e la varianza. Va bene lo stesso?

****************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include "random.h"

using namespace std;

double error(double mean, double squaremean, int N){

	if (N==0)
		return 0;
	else
		return sqrt( (squaremean-mean*mean)/static_cast<double>(N) );
}

int main (int argc, char *argv[]){

  Random rnd;
  rnd.Initialize();
   
  int M=100000;       //total number of throws
  int N=1000;          //size of blocks
  int L=(int)(M/N);   //number of blocks
  
  std::vector<double> block_values, quadratic_distances;
   
  for(int i=0; i<L; ++i) {
    double sum=0,sumQD=0;
    for(int j=0; j<N; ++j){
    	sum+=rnd.Rannyu();             //accumulator for mean
    	sumQD+=pow(rnd.Rannyu()-.5,2); //accumulator for variance
    }
    
		block_values.push_back(sum/static_cast<double>(N));
		quadratic_distances.push_back(sumQD/static_cast<double>(N));
  }
  
  vector<double> cumulative_means, cumulative_square_means, errors;
  ofstream outM("data/1means.dat"), outVAR("data/1vars.dat");
  
  for(int i=0; i<L; ++i) {
  	double sum=0, sum2=0, sumQD=0, sumQD2=0;
  	for(int j=0; j<i+1; ++j){
  		sum+=block_values.at(j);
  		sum2+=block_values.at(j)*block_values.at(j);
  		sumQD+=quadratic_distances.at(j);
  		sumQD2+=quadratic_distances.at(j)*quadratic_distances.at(j);
  	}
  	
  	if(outM.good())
  		outM << sum/static_cast<double>(i+1) << " " << error(sum/static_cast<double>(i+1),sum2/static_cast<double>(i+1),i ) << endl;
  	if(outVAR.good())
  	  outVAR << sumQD/static_cast<double>(i+1) << " " << error(sumQD/static_cast<double>(i+1),sumQD2/static_cast<double>(i+1),i ) << endl;
  }
  outM.close();
  outVAR.close();
  
  //chi square test
  
  M=100;                 //(fixed) number of intervals in [0,1]
  int n=10000;           //number of throws for each test
  int iterations = 100;  //number of simulations
  double expected_throws = static_cast<double>(n)/static_cast<double>(M);
                         //(throws exected for each interval - parameter)
  
  ofstream outCHI("data/1Chi.dat");
  
  vector<int> intervals(M);     //representing a counter for each interval
                                //to count the number of throws falling in it
  
  for(int j=0; j<iterations; ++j) {
  
	fill(intervals.begin(), intervals.end(), 0); //initializing
	double tmp_chi=0;
  
		for(int i=0; i<n; ++i)
			++intervals.at(rnd.Rannyu()/0.01);  //generating values and incrementing the
			                                    //correspondent intervals counter
		
		for(auto it=intervals.begin(); it!=intervals.end(); ++it)
			tmp_chi+=pow(*it-expected_throws,2)/expected_throws;
		
		if(outCHI.good()) outCHI << tmp_chi << endl;

  }
  
  outCHI.close();

  return 0;
}
