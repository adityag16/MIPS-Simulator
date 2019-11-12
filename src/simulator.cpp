#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include "decode.hpp"
#include "mips_instructions.hpp"
#include "memory.hpp"

int main(int argc, char* argv[]){
	
	std::vector<uint8_t> imem;
	imem.resize(IMEMLENGTH);
	std::vector<uint8_t> dmem;
	dmem.resize(0x4000000);
	std::fill(imem.begin(), imem.end(), 0);
	uint32_t pc = IMEMOFFSET;
	uint32_t nextpc = pc+4;
	int32_t registers[32] = {0};
	std::ifstream::pos_type size_of_bin;
	int32_t HI = 0,LO = 0;
	std::vector<uint32_t> instruction_segments;
	std::string binary_num; //declarations
	

	std::ifstream binStream;
	binStream.open(argv[1], std::ios::in | std::ios::binary | std::ios::ate);
	if (binStream.is_open()){
		size_of_bin = binStream.tellg();
		binStream.seekg(0,std::ios::beg);
		binary_num.resize(size_of_bin);
		binStream.read(&binary_num[0], size_of_bin);// read and open files. writes them to binary_num
	}
	else{
		exit(-21);
	}
	binStream.close();
	store_into_imem(size_of_bin, binary_num, imem);
	while(pc!=0){
		
		if(pc<IMEMOFFSET || pc> IMEMOFFSET + IMEMLENGTH){
		exit(-12);
		}
		else{
			for (int i = 0 ; i < size_of_bin; i++){
				uint32_t instruction = pull_word_from_memory(imem, i);
				uint32_t tmp =Instruction_decode(instruction, instruction_segments);
				instruction_rc retcode = MIPS_instruction(registers, HI, LO, pc, nextpc, dmem, instruction_segments, imem);
				std::cerr<<std::endl;
				std::cerr<< registers[instruction_segments[1]]<< " rs" << std::endl;
				std::cerr<< registers[instruction_segments[2]]<< " rt" << std::endl;
				std::cerr<< registers[instruction_segments[3]]<< " rd" << std::endl;

				std::cerr<< pc << "  pc "<<std::endl;
				instruction_segments.clear();
				std::cerr<<std::endl;
				i+=3;// creates instructions from memory
		}
		exit(0);
		}
	}
	
return 0;
}


