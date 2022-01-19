/****************************************************************

author:gilberto.nardi@studenti.unimi.it
date: Mar 18th, 2021

code to test the 'Random' class

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
  rnd.Initialize(3);
   
  int B=100;      //number of blocks
  int N=100;      //size of blocks
  int M=B*N;      //total throws
  
  //variables to store the progressive mean value of the sequence
  double prog_mean=0, prog_mean2=0,
         prog_QDmean=0, prog_QDmean2=0;

  ofstream outM("data/1means.dat"), outVAR("data/1vars.dat");
  
  //estimating <r>
  for(int j=0; j<B; ++j) { 
    double accu=0;
    for(int i=0; i<N; ++i){
  	  accu+=rnd.Rannyu();
    }
  	prog_mean=((prog_mean*j+accu/N)/(j+1));
  	prog_mean2=(prog_mean2*j+pow(accu/N,2))/(j+1);
    if(outM.good())
    	outM << prog_mean << " " << error(prog_mean,prog_mean2,j) << endl; 
  }

  //estimating standard deviation
  for(int j=0; j<B; ++j) {
  
    double accu=0;
    for(int i=0; i<N; ++i){
      accu+=pow(rnd.Rannyu()-0.5,2);
    }
    prog_QDmean=((prog_QDmean*j+accu/N)/(j+1));
    prog_QDmean2=(prog_QDmean2*j+pow(accu/N,2))/(j+1);
    if(outVAR.good())
      outVAR << prog_QDmean << " " << error(prog_QDmean,prog_QDmean2,j) << endl; 

  }
  
  outM.close();
  outVAR.close();
  
  //chi square test  
  M=100;                 //(fixed) number of intervals in [0,1]
  int n=10000;           //number of throws for each test
  int iterations = 100;  //number of simulations (chi square calculations)
  double expected_throws = static_cast<double>(n)/static_cast<double>(M); //expectation value - # of throws for each interval
  
  ofstream outCHI("data/1Chi.dat");
  
  vector<int> intervals(M);     //representing a counter for each interval
                                //to count the number of throws falling in it
  
  for(int j=0; j<iterations; ++j) {
  
    fill(intervals.begin(), intervals.end(), 0); //initializing
    double tmp_chi=0;
  
		for(int i=0; i<n; ++i)
			++intervals.at(rnd.Rannyu(0.,double(M)));  //generating values and incrementing the
			                                           //correspondent intervals counter
		
		for(auto it=intervals.begin(); it!=intervals.end(); ++it)
			tmp_chi+=pow(*it-expected_throws,2)/expected_throws;
		
		if(outCHI.good()) outCHI << tmp_chi << endl;

  }
  
  outCHI.close();
  rnd.SaveSeed();

  return 0;
}
