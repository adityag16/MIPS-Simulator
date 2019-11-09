#ifndef DECODE_HPP
#define DECODE_HPP

#include <iostream> 
#include <vector>
void R_decode(const uint32_t &binary_instruction, std::vector<uint32_t>& instruction_segments);

void I_decode(const uint32_t &binary_instruction, std::vector<uint32_t>& instruction_segments);

void J_decode(const uint32_t &binary_instruction, std::vector<uint32_t>& instruction_segments);

uint32_t Instruction_decode(const uint32_t &binary_instruction, std::vector<uint32_t>& instruction_segments);

#endif