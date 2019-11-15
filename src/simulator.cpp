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
	
	std::vector<uint8_t> Instruction_Memory;
	Instruction_Memory.resize(IMEMLENGTH);
	std::vector<uint8_t> Data_Memory;
	Data_Memory.resize(DMEMLENGTH);

	std::fill(Instruction_Memory.begin(), Instruction_Memory.end(), 0);
	std::fill(Data_Memory.begin(), Data_Memory.end(), 0);

	uint32_t PC = IMEMOFFSET;
	uint32_t Next_PC = PC+4;
	int32_t registers[32] = {0};
	int32_t HI = 0,LO = 0;
	
	std::ifstream::pos_type size_of_bin;
	
	uint32_t instruction_segments[6] = {0};
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
	store_into_imem(size_of_bin, binary_num, Instruction_Memory);
	
	while(PC!=0){
		if(PC<IMEMOFFSET || PC> IMEMOFFSET + IMEMLENGTH || PC % 4 != 0){
			std::exit(Memory_Exception);
		}
		int index = imem_address_to_index(PC);
		uint32_t instruction = pull_word_from_memory(Instruction_Memory, index);
		uint32_t tmp = Instruction_decode(instruction, instruction_segments);
		instruction_rc retcode = MIPS_instruction(registers, HI, LO, PC, Next_PC, Data_Memory, instruction_segments, Instruction_Memory);

	}
	std::exit(registers[2] & 0xFF);
	return 0;
}


