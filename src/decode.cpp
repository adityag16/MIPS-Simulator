#include "decode.hpp"
#include <iostream> 
#include <vector>

uint32_t Instruction_decode(const uint32_t &binary_instruction, uint32_t* instruction_segments){
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

void R_decode(const uint32_t &binary_instruction, uint32_t* instruction_segments){
    instruction_segments[0] = uint32_t (binary_instruction >> 26);
    instruction_segments[1] = uint32_t ((binary_instruction & 0x03E00000) >> 21);
    instruction_segments[2] = uint32_t ((binary_instruction & 0x001F0000) >> 16);
    instruction_segments[3] = uint32_t ((binary_instruction & 0x0000F800) >> 11);
    instruction_segments[4] = uint32_t ((binary_instruction & 0x000007C0) >> 6);
    instruction_segments[5] = uint32_t (binary_instruction & 0x0000003F);

}

void I_decode(const uint32_t &binary_instruction, uint32_t* instruction_segments){
    instruction_segments[0] = uint32_t (binary_instruction >> 26) ;
    instruction_segments[1] = uint32_t ((binary_instruction & 0x03E00000) >> 21);
    instruction_segments[2] = uint32_t ((binary_instruction & 0x001F0000) >> 16);
    instruction_segments[3] = uint32_t (binary_instruction & 0x0000FFFF);

}

void J_decode(const uint32_t &binary_instruction, uint32_t* instruction_segments){
    instruction_segments[0] = uint32_t (binary_instruction >> 26);
    instruction_segments[1] = uint32_t (binary_instruction & 0x003FFFFF);
}