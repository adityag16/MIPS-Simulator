#include "decode.hpp"
#include <iostream> 
#include <vector>

uint32_t Instruction_decode(const uint32_t &binary_instruction, std::vector<uint32_t>& instruction_segments){
    uint32_t instruction_opcode = binary_instruction >> 26;

    if(instruction_opcode == 0){
        R_decode(binary_instruction, instruction_segments);
    }
    else if(instruction_opcode == 2 || instruction_opcode == 3){
        J_decode(binary_instruction, instruction_segments);
    }
    else{
        I_decode(binary_instruction, instruction_segments);
    }

    return 0; 
}

void R_decode(const uint32_t &binary_instruction, std::vector<uint32_t>& instruction_segments){
    uint32_t opcode = binary_instruction >> 26;
    uint32_t source1 = (binary_instruction & 0x03E00000) >> 21;
    uint32_t source2 = (binary_instruction & 0x001F0000) >> 16;
    uint32_t dest = (binary_instruction & 0x0000F800) >> 11;
    uint32_t shift = (binary_instruction & 0x000007C0) >> 6;
    uint32_t function_code = binary_instruction & 0x0000003F;

    instruction_segments.push_back(opcode);
    instruction_segments.push_back(source1);
    instruction_segments.push_back(source2);
    instruction_segments.push_back(dest);
    instruction_segments.push_back(shift);
    instruction_segments.push_back(function_code);
}

void I_decode(const uint32_t &binary_instruction, std::vector<uint32_t>& instruction_segments){
    uint32_t opcode = binary_instruction >> 26 ;
    uint32_t source1 = (binary_instruction & 0x03E00000) >> 21;
    uint32_t dest = (binary_instruction & 0x001F0000) >> 16;
    uint32_t constant = binary_instruction & 0x0000FFFF;

    instruction_segments.push_back(opcode);
    instruction_segments.push_back(source1);
    instruction_segments.push_back(dest);
    instruction_segments.push_back(constant);
}

void J_decode(const uint32_t &binary_instruction, std::vector<uint32_t>& instruction_segments){
    uint32_t opcode = binary_instruction >> 26;
    uint32_t address = binary_instruction & 0x003FFFFF;

    instruction_segments.push_back(opcode);
    instruction_segments.push_back(address);
}