#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include <iostream>
#include <vector>

typedef int32_t instruction_rc;

#define Arithmetic_Exception -10
#define Memory_Exception -11
#define Invalid_Instruction -12
#define Internal_Error -20

instruction_rc MIPS_instruction(int32_t* registers, int32_t &HI, int32_t &LO, uint32_t &PC, uint32_t &next_PC, std::vector<uint8_t>& Data_mem, uint32_t* instruction_segments, std::vector<uint8_t>& Instruction_mem);

instruction_rc ADD(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc ADDI(const int32_t &rs, int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC);

instruction_rc ADDIU(const int32_t &rs, int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC);

instruction_rc ADDU(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc AND(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc ANDI(const int32_t &rs, int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC);

instruction_rc BEQ(const int32_t &rs, const int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC);

instruction_rc BGEZ(const int32_t &rs, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments); 

instruction_rc BGEZAL(const int32_t &rs, const int16_t &immediate, uint32_t &PC, int32_t &reg31, uint32_t &next_PC, uint32_t* instruction_segments); 

instruction_rc BGTZ(const int32_t &rs, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc BLEZ(const int32_t &rs, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc BLTZ(const int32_t &rs, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments); 

instruction_rc BLTZAL(const int32_t &rs, const int16_t &immediate, uint32_t &PC, int32_t &reg31, uint32_t &next_PC, uint32_t* instruction_segments); 

instruction_rc BNE(const int32_t &rs, const int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC);

instruction_rc DIV(const int32_t &rs, const int32_t &rt, uint32_t &PC, uint32_t &next_PC, int32_t &HI, int32_t &LO, uint32_t* instruction_segments);

instruction_rc DIVU(const int32_t &rs, const int32_t &rt, uint32_t &PC, uint32_t &next_PC, int32_t &HI, int32_t &LO, uint32_t* instruction_segments);

instruction_rc J(const uint32_t &instr_index, uint32_t &PC, uint32_t &next_PC);

instruction_rc JAL(const uint16_t &instr_index, uint32_t &PC, uint32_t &next_PC, int32_t &reg31);

instruction_rc JR(const int32_t &rs, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc MFHI(int32_t &rd, uint32_t &PC, uint32_t &next_PC, const int32_t &HI, uint32_t* instruction_segments);

instruction_rc MFLO(int32_t &rd, uint32_t &PC, uint32_t &next_PC, const int32_t &LO, uint32_t* instruction_segments);

instruction_rc MTHI(const int32_t &rs, uint32_t &PC, uint32_t &next_PC, int32_t &HI, uint32_t* instruction_segments);

instruction_rc MTLO(const int32_t &rs, uint32_t &PC, uint32_t &next_PC, int32_t &LO, uint32_t* instruction_segments);

instruction_rc MULT(const int32_t &rs, const int32_t &rt, uint32_t &PC, uint32_t &next_PC, int32_t &HI, int32_t &LO, uint32_t* instruction_segments);

instruction_rc MULTU(const int32_t &rs, const int32_t &rt, uint32_t &PC, uint32_t &next_PC, int32_t &HI, int32_t &LO, uint32_t* instruction_segments);

instruction_rc OR(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc ORI(const int32_t &rs, int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC);

instruction_rc SLL(const uint32_t &sa, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc SLLV(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc SLT(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc SLTI(const int32_t &rs, int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC);

instruction_rc SLTIU(const int32_t &rs, int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC);

instruction_rc SLTU(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc SRA(const int32_t &sa, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc SRAV(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc SRL(const int32_t &sa, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc SRLV(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc SUB(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc SUBU(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc XOR(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc XORI(const int32_t &rs, int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC);

instruction_rc LW(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC, const std::vector<uint8_t>& Data_mem, const std::vector<uint8_t>& Instruction_mem);

instruction_rc SW(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC, std::vector<uint8_t>& Data_mem);

instruction_rc LB(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC, const std::vector<uint8_t>& Data_mem, const std::vector<uint8_t>& Instruction_mem);

instruction_rc LH(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC, const std::vector<uint8_t>& Data_mem, const std::vector<uint8_t>& Instruction_mem);

instruction_rc LBU(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC, const std::vector<uint8_t>& Data_mem, const std::vector<uint8_t>& Instruction_mem);

instruction_rc LHU(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC, const std::vector<uint8_t>& Data_mem, const std::vector<uint8_t>& Instruction_mem);

instruction_rc LUI(int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc JALR(const int32_t &rs, int32_t &rd, uint32_t &PC, uint32_t &next_PC, uint32_t* instruction_segments);

instruction_rc SB(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC, std::vector<uint8_t>& Data_mem);

instruction_rc SH(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC, std::vector<uint8_t>& Data_mem);

instruction_rc LWL(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC, const std::vector<uint8_t>& Data_mem, const std::vector<uint8_t>& Instruction_mem);

instruction_rc LWR(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC, const std::vector<uint8_t>& Data_mem, const std::vector<uint8_t>& Instruction_mem);

#endif
