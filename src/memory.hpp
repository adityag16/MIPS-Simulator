#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <vector>
#include <iostream>
#define IMEMOFFSET 0x10000000
#define IMEMLENGTH 0x1000000
#define DMEMOFFSET 0x20000000
#define DMEMLENGTH 0x4000000
#define ADDR_GETC 0x30000000
#define ADDR_PUTC 0x30000004

uint32_t imem_address_to_index(uint32_t memaddress);

uint32_t index_to_imemaddress(uint32_t index);

uint32_t dmem_address_to_index(uint32_t memaddress);

uint32_t index_to_dmemaddress(uint32_t index);

uint32_t pull_word_from_memory(const std::vector<uint8_t>& mem, uint32_t index);

uint32_t pull_byte_from_memory(const std::vector<uint8_t>& mem, uint32_t index);

uint32_t pull_hword_from_memory(const std::vector<uint8_t>& mem, uint32_t index);

void store_word_to_memory(std::vector<uint8_t>& mem, uint32_t index, int32_t rt);

void store_hword_to_memory(std::vector<uint8_t>& mem, uint32_t index, int32_t rt);

void store_into_imem(uint32_t size_of_bin, std::string binary_num, std::vector<uint8_t> &imem);

int32_t get_c();

void lwl_helper(const std::vector<uint8_t>& mem, uint32_t index, int32_t &rt, int32_t mem_address);

void lwr_helper(const std::vector<uint8_t>& mem, uint32_t index, int32_t &rt, int32_t mem_address);

#endif