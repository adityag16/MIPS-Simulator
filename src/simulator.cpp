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
	std::fill(dmem.begin(), dmem.end(), 0);

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
		std::exit(-21);
	}
	binStream.close();
	store_into_imem(size_of_bin, binary_num, imem);
	while(pc!=0){
		if((pc<IMEMOFFSET || pc> IMEMOFFSET + IMEMLENGTH) && (pc % 4 != 0)){
			std::exit(Memory_Exception);
		}
		int index = imem_address_to_index(pc);
		uint32_t instruction = pull_word_from_memory(imem, index);
		uint32_t tmp = Instruction_decode(instruction, instruction_segments);
		instruction_rc retcode = MIPS_instruction(registers, HI, LO, pc, nextpc, dmem, instruction_segments, imem);
		instruction_segments.clear();

	}
	std::exit(registers[2] & 0xFF);
	return 0;
}


