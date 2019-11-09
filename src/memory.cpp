#include "memory.hpp"
#include "mips_instructions.hpp"
#include <iostream>
#include <vector>
#include <bitset>

uint32_t imem_address_to_index(uint32_t memaddress){
	return memaddress-0x10000000;
}
uint32_t index_to_imemaddress(uint32_t index){
	return index+0x10000000;
}
uint32_t dmem_address_to_index(uint32_t memaddress){
	return memaddress-0x20000000;
}
uint32_t index_to_dmemaddress(uint32_t index){
	return index+0x20000000;
}
uint32_t pull_word_from_memory(std::vector<uint8_t> mem, uint32_t index){
	return (mem[index] << 24) + (mem[index+1] << 16) + (mem[index+2]<< 8) + (mem[index+3]);
}

uint32_t pull_byte_from_memory(std::vector<uint8_t> mem, uint32_t index){
	uint32_t load_val = mem[index];
	return load_val;
}

uint32_t pull_hword_from_memory(std::vector<uint8_t> mem, uint32_t index){
	return (mem[index] << 8) + (mem[index+1]);
}


void store_word_to_memory(std::vector<uint8_t>& mem, uint32_t index, int32_t rt){
	uint8_t byte_0 = rt >> 24;
	uint8_t byte_1 = (rt & 0x00FF0000) >> 16;
	uint8_t byte_2 = (rt & 0x0000FF00) >> 8;
	uint8_t byte_3 = rt & 0x000000FF;

	mem[index] = byte_0;
	mem[index + 1] = byte_1;
	mem[index + 2] = byte_2;
	mem[index + 3] = byte_3;

}


void store_hword_to_memory(std::vector<uint8_t>& mem, uint32_t index, int32_t rt){
	uint8_t byte_0 = (rt & 0x0000FF00) >> 8;
	uint8_t byte_1 = rt & 0x000000FF;

	mem[index] = byte_0;
	mem[index + 1] = byte_1;
}

void store_into_imem(uint32_t size_of_bin, std::string binary_num, std::vector<uint8_t> &imem){
	for (int i = 0 ; i < size_of_bin; i++){
		std::bitset<8>bin_i(binary_num[i]);
		imem[i]= bin_i.to_ulong();// converts bitsets to ints and stores in mem
	}
}

int32_t get_c(){
	int32_t Char_in = std::getchar();
           
	if(Char_in != std::cin.eof() && Char_in != EOF){
		return Char_in;
	}
	else{
		return -1;
	}
}
 