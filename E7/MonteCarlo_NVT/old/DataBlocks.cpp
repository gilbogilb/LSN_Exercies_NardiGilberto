//implementing DataBlocks.h classes

#include "DataBlocks.h"

		
DataBlockingTool::DataBlockingTool(const char* output_name, int block_size){

	out.open(output_name);

	if(!out.good()){
		std::cout << "error: can't open " << output_name << std::endl;
		exit(1);
	}
	
	m_prog_mean  = 0;
	m_prog_mean2 = 0;
	m_N = 0;
	m_err = 0.;

	m_block_prog_mean = 0;
	m_actual_block_size = 0;
	m_block_size = block_size;
	
}

DataBlockingTool::~DataBlockingTool(){
	out.close();
}

void
DataBlockingTool::AppendBlock(double block) {

	m_prog_mean  = (m_prog_mean*m_N+block)/static_cast<double>(m_N+1);
	m_prog_mean2 = (m_prog_mean2*m_N+block*block)/static_cast<double>(m_N+1);
	++m_N;
	if(m_N>1)
		m_err = sqrt((m_prog_mean2-m_prog_mean*m_prog_mean)/static_cast<double>(m_N-1));

}

void
DataBlockingTool::Write() {

	if(out.good()){	
		out << m_prog_mean << " " << m_err << std::endl;
	}
	else{
		std::cerr << "error: broken ofstream. end\n";
		exit(-1);
	}

}

void
DataBlockingTool::AppendValue(double val){

	//calculating the progressive mean for the current block
	m_block_prog_mean = (m_block_prog_mean*m_actual_block_size + val)/static_cast<double>(m_actual_block_size+1);
	m_actual_block_size += 1;

	//if the block is full
	if(m_actual_block_size == m_block_size){

		AppendBlock(m_block_prog_mean);
		Write();
		m_block_prog_mean = 0;
		m_actual_block_size = 0;
	}
}

void
DataBlockingTool::Reset(const char * output_name, int block_size){

	out.close();

	out.open(output_name,std::ios::app);

	if(!out.good()){
		std::cout << "error: can't open " << output_name << std::endl;
		exit(1);
	}

	out << std::endl;
	
	m_prog_mean  = 0;
	m_prog_mean2 = 0;
	m_N = 0;
	m_err = 0.;

	m_block_prog_mean = 0;
	m_actual_block_size = 0;
	m_block_size = block_size;
	

}