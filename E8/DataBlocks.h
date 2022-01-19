/*

Data Blocking Tool: automatically writes progressive means
and statistical uncertainties with Data Blocking method.

author: gilberto.nardi@studenti.unimi.it
date  : Apr 15th, 2021

*/

#ifndef DATA_BLOCKS_H
#define DATA_BLOCKS_H

#include <fstream>
#include <iostream>
#include <cmath>


class 
DataBlockingTool {

	public:
		DataBlockingTool(const char* output_name, int block_size);
		~DataBlockingTool();

		void AppendValue(double val);

		double GetMean() const {return m_prog_mean;}
		double GetError() const;
		double GetBlocksN() const {return m_N;}
	
	private:

	std::ofstream out;

	double m_prog_mean;        //dealing with multiple blocks
	double m_prog_mean2;
	int    m_N; //number of blocks

	double m_block_prog_mean;  //dealing with single block
	int m_block_size, m_actual_block_size;
	
	void m_AppendBlock(double block); //auxiliary functions, called
	void m_Write();                   //by AppendValue if the block is full

};

#endif /*DATA_BLOCKS_H*/
