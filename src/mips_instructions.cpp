#include "memory.hpp"
#include "mips_instructions.hpp"
#include <bitset>

instruction_rc MIPS_instruction(int32_t* registers, int32_t &HI, int32_t &LO, uint32_t &PC, uint32_t &next_PC, std::vector<uint8_t>& Data_mem, const std::vector<uint32_t>& instruction_segments, std::vector<uint8_t>& Instruction_mem){
    uint32_t opcode = instruction_segments[0];
    instruction_rc return_code; 

    if(opcode == 0b0000000){ // Condition for R type instruction 
        uint32_t rs = instruction_segments[1];
        uint32_t rt = instruction_segments[2];
        uint32_t rd = instruction_segments[3];
        uint32_t sa = instruction_segments[4];

        uint32_t function_code = instruction_segments[5];

        switch(function_code){
            case 0b100000: return_code =  ADD(registers[rs], registers[rt], registers[rd], PC, next_PC);
            break;
            case 0b100001: return_code =  ADDU(registers[rs], registers[rt], registers[rd], PC, next_PC);
            break; 
            case 0b100010: return_code =  SUB(registers[rs], registers[rt], registers[rd], PC, next_PC);
            break;
            case 0b100100: return_code =  AND(registers[rs], registers[rt], registers[rd], PC, next_PC);
            break;
            case 0b011010: return_code =  DIV(registers[rs], registers[rt], PC, next_PC, HI, LO);
            break;
            case 0b011011: return_code =  DIVU(registers[rs], registers[rt], PC, next_PC, HI, LO);
            break; 
            case 0b001000: return_code =  JR(registers[rs], PC, next_PC);
            break;
            case 0b010000: return_code =  MFHI(registers[rd], PC, next_PC, HI);
            break; 
            case 0b010010: return_code =  MFLO(registers[rd], PC, next_PC, LO);
            break;
            case 0b010001: return_code =  MTHI(registers[rs], PC, next_PC, HI);
            break;
            case 0b010011: return_code =  MTLO(registers[rs], PC, next_PC, LO);
            break;
            case 0b011000: return_code =  MULT(registers[rs], registers[rt], PC, next_PC, HI, LO);
            break;
            case 0b011001: return_code =  MULTU(registers[rs], registers[rt], PC, next_PC, HI, LO);
            break; 
            case 0b100101: return_code =  OR(registers[rs], registers[rt], registers[rd], PC, next_PC);
            break;
            case 0b000000: return_code =  SLL(sa, registers[rt], registers[rd], PC, next_PC);
            break;
            case 0b000100: return_code =  SLLV(registers[rs], registers[rt], registers[rd], PC, next_PC);
            break; 
            case 0b101010: return_code =  SLT(registers[rs], registers[rt], registers[rd], PC, next_PC);
            break;
            case 0b101011: return_code =  SLTU(registers[rs], registers[rt], registers[rd], PC, next_PC);
            break;
            case 0b000011: return_code =  SRA(sa, registers[rt], registers[rd], PC, next_PC);
            break;
            case 0b000111: return_code =  SRAV(registers[rs], registers[rt], registers[rd], PC, next_PC);
            break;
            case 0b100110: return_code =  XOR(registers[rs], registers[rt], registers[rd], PC, next_PC);
            break;
            case 0b100011: return_code =  SUBU(registers[rs], registers[rt], registers[rd], PC, next_PC);
            break;
            case 0b000110: return_code =  SRLV(registers[rs], registers[rt], registers[rd], PC, next_PC);
            break;
            case 0b000010: return_code =  SRL(sa, registers[rt], registers[rd], PC, next_PC);
            break;
            case 0b001001: return_code =  JALR(registers[rs], registers[rd], PC, next_PC);
            break;

            default: std::exit(Invalid_Instruction);
        }
    }
    else if(opcode == 0b000010 || opcode == 0b000011){ // J Type
        uint32_t inst_index = instruction_segments[1];
        
        if(opcode == 0b000010){
            return_code =  J(inst_index, PC, next_PC);
        }
        else if(opcode == 0b000011){
            return_code =  JAL(inst_index, PC, next_PC, registers[31]);
        }
        else{
            std::exit(Invalid_Instruction);
        }
        
    }
    else{ // I Type
        uint32_t rs = instruction_segments[1];
        uint32_t base = instruction_segments[1];

        uint32_t rt = instruction_segments[2];
        uint32_t offset = instruction_segments[3]; 

        switch(opcode){
            case 0b001000: return_code =  ADDI(registers[rs], registers[rt], offset, PC, next_PC);
            break;
            case 0b001001: return_code =  ADDIU(registers[rs], registers[rt], offset, PC, next_PC);
            break;
            case 0b001100: return_code =  ANDI(registers[rs], registers[rt], offset, PC, next_PC);
            break;
            case 0b000100: return_code =  BEQ(registers[rs], registers[rt], offset, PC, next_PC);
            break;
            case 0b000111: return_code =  BGTZ(registers[rs], offset, PC, next_PC);
            break;
            case 0b000110: return_code =  BLEZ(registers[rs], offset, PC, next_PC);
            break;
            case 0b000101: return_code =  BNE(registers[rs], registers[rt], offset, PC, next_PC);
            break;
            case 0b001101: return_code =  ORI(registers[rs], registers[rt], offset, PC, next_PC);
            break;
            case 0b001010: return_code =  SLTI(registers[rs], registers[rt], offset, PC, next_PC);
            break;
            case 0b001011: return_code =  SLTIU(registers[rs], registers[rt], offset, PC, next_PC);
            break;
            case 0b001110: return_code =  XORI(registers[rs], registers[rt], offset, PC, next_PC);
            break;
            case 0b000001: 
                if(instruction_segments[2] == 0b00001){
                    return_code =  BGEZ(registers[rs], offset, PC, next_PC);
                }   
                else if(instruction_segments[2] == 0b10001){
                    return_code =  BGEZAL(registers[rs], offset, PC, registers[31], next_PC);
                }
                else if(instruction_segments[2] == 0b00000){
                    return_code =  BLTZ(registers[rs], offset, PC, next_PC);
                }
                else if(instruction_segments[2] == 0b10000){
                    return_code =  BLTZAL(registers[rs], offset, PC, registers[31], next_PC);
                }
            break;
            case 0b101011: return_code =  SW(registers[base], registers[rt], offset, PC, next_PC, Data_mem);
            break;
            case 0b100011: return_code =  LW(registers[base], registers[rt], offset, PC, next_PC, Data_mem, Instruction_mem);
            break;
            case 0b100001: return_code =  LH(registers[base], registers[rt], offset, PC, next_PC, Data_mem, Instruction_mem);
            break;
            case 0b100000: return_code =  LB(registers[base], registers[rt], offset, PC, next_PC, Data_mem, Instruction_mem);
            break;
            case 0b100100: return_code =  LBU(registers[base], registers[rt], offset, PC, next_PC, Data_mem, Instruction_mem);
            break;
            case 0b100101: return_code =  LHU(registers[base], registers[rt], offset, PC, next_PC, Data_mem, Instruction_mem);
            break;
            case 0b001111: return_code =  LUI(registers[rt], offset, PC, next_PC);
            break;
            case 0b101000: return_code =  SB(registers[base], registers[rt], offset, PC, next_PC, Data_mem);
            break;
            case 0b101001: return_code =  SH(registers[base], registers[rt], offset, PC, next_PC, Data_mem);
            break;
            case 0b100010: return_code = LWL(registers[base], registers[rt], offset, PC, next_PC, Data_mem, Instruction_mem);
            break;
            default: std::exit(Invalid_Instruction);
        }

    }
    registers[0] = 0; 
    return return_code;
}

// intialise PC and next_pc = PC + 4
instruction_rc ADD(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC){
    if((rt < 0) && (rs < 0) && (rt + rs >= 0)){
        std::exit(Arithmetic_Exception);
    }
    else if((rt >= 0) && (rs >= 0) && (rs + rt < 0)){
        std::exit(Arithmetic_Exception);
    }
    else{
        rd =  rs + rt;
        PC = next_PC;
        next_PC += 4;
    }

    return 0;
}

instruction_rc ADDI(const int32_t &rs, int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC){
    int32_t sign_extended_const = immediate;

    if((rs < 0) && (sign_extended_const < 0) && (rs + sign_extended_const >=0)){
        std::exit(Arithmetic_Exception);
    }
    else if((rs >= 0) && (sign_extended_const >= 0) && (rs + sign_extended_const < 0)){
        std::exit(Arithmetic_Exception);
    }
    else{
        rt = rs + sign_extended_const;
        PC = next_PC;
        next_PC += 4;

    }
    return 0;
}

instruction_rc ADDIU(const int32_t &rs, int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC){
    int32_t sign_extended_const = immediate;

    rt = rs + sign_extended_const;
    PC = next_PC;
    next_PC += 4;
    
    return 0;
}

instruction_rc ADDU(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC){
    rd = rt + rs;
    PC = next_PC;
    next_PC += 4;

    return 0;
}

instruction_rc AND(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC){
    rd = rs & rt;
    PC = next_PC;
    next_PC += 4;

    return 0;

}

instruction_rc ANDI(const int32_t &rs, int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC){
    uint32_t zero_extended_const = immediate;

    rt = rs & zero_extended_const;
    PC = next_PC;
    next_PC += 4;

    return 0;
}

instruction_rc BEQ(const int32_t &rs, const int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC){
    int32_t offset = immediate << 2;

    if(rs == rt){
        PC = next_PC;
        next_PC = PC + offset;
    }
    else{
        PC = next_PC;
        next_PC += 4;
    }

    return 0;
}

instruction_rc BGEZ(const int32_t &rs, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC){
    int32_t offset = immediate << 2;

    if(rs >= 0){
        PC = next_PC;
        next_PC = PC + offset;
    }
    else{
        PC = next_PC;
        next_PC += 4;
    }

    return 0;
}

instruction_rc BGEZAL(const int32_t &rs, const int16_t &immediate, uint32_t &PC, int32_t &reg31, uint32_t &next_PC){
    int32_t offset = immediate << 2;

    if(rs >= 0){
        reg31 = PC + 8;
        PC = next_PC;
        next_PC = PC + offset;
    }
    else{
        PC = next_PC;
        next_PC += 4;
    }

    return 0;
}

instruction_rc BGTZ(const int32_t &rs, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC){
    int32_t offset = immediate << 2;

    if(rs > 0){
        PC = next_PC;
        next_PC = PC + offset;
    }
    else{
        PC = next_PC;
        next_PC += 4;
    }

    return 0;
}

instruction_rc BLEZ(const int32_t &rs, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC){
    int32_t offset = immediate << 2;

    if(rs <= 0){
        PC = next_PC;
        next_PC = PC + offset;
    }
    else{
        PC = next_PC;
        next_PC += 4;
    }

    return 0;
}

instruction_rc BLTZ(const int32_t &rs, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC){
    int32_t offset = immediate << 2;

    if(rs < 0){
        PC = next_PC;
        next_PC = PC + offset;
    }
    else{
        PC = next_PC;
        next_PC += 4;
    }

    return 0;

}

instruction_rc BLTZAL(const int32_t &rs, const int16_t &immediate, uint32_t &PC, int32_t &reg31, uint32_t &next_PC){
    int32_t offset = immediate << 2;

    if(rs < 0){
        reg31 = PC + 8;
        PC = next_PC;
        next_PC = PC + offset;
    }
    else{
        PC = next_PC;
        next_PC += 4;
    }

    return 0;    
}

instruction_rc BNE(const int32_t &rs, const int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC){
    int32_t offset = immediate << 2;

    if(rs != rt){
        PC = next_PC;
        next_PC = PC + offset;
    }
    else{
        PC = next_PC;
        next_PC += 4;
    }

    return 0;
}

instruction_rc DIV(const int32_t &rs, const int32_t &rt, uint32_t &PC, uint32_t &next_PC, int32_t &HI, int32_t &LO){

    if(rt != 0){
        LO = rs / rt;
        HI = rs % rt; 
    }

    PC = next_PC;
    next_PC += 4; 

    return 0; 
}

instruction_rc DIVU(const int32_t &rs, const int32_t &rt, uint32_t &PC, uint32_t &next_PC, int32_t &HI, int32_t &LO){

    if(rt != 0){
        LO = rs / rt;
        HI = rs % rt; 
    }

    PC = next_PC;
    next_PC += 4; 

    return 0; 
}

instruction_rc J(const uint16_t &instr_index, uint32_t &PC, uint32_t &next_PC){
    uint32_t shifted_instr_index = instr_index << 2;
    uint32_t upper_bits = next_PC & 0xF0000000;

    PC = next_PC;
    next_PC = upper_bits + shifted_instr_index; 

    return 0;
}

instruction_rc JAL(const uint16_t &instr_index, uint32_t &PC, uint32_t &next_PC, int32_t &reg31){
    uint32_t shifted_instr_index = instr_index << 2;
    uint32_t upper_bits = next_PC & 0xF0000000;

    reg31 = PC + 8;
    PC = next_PC;
    next_PC = upper_bits + shifted_instr_index; 

    return 0;
}

instruction_rc JALR(const int32_t &rs, int32_t &rd, uint32_t &PC, uint32_t &next_PC){
    rd = PC + 8;
    PC = next_PC;
    next_PC =  rs;

    return 0;
}

instruction_rc JR(const int32_t &rs, uint32_t &PC, uint32_t &next_PC){
    PC = next_PC;
    next_PC =  rs;

    return 0;
}

instruction_rc LB(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC,std::vector<uint8_t> Data_mem, std::vector<uint8_t> Instruction_mem){
    int32_t sign_ext_offset = offset;
    int32_t mem_address = base + sign_ext_offset; 

    if(mem_address <= DMEMOFFSET + DMEMLENGTH && mem_address >= DMEMOFFSET){
        uint32_t dmem_index = dmem_address_to_index(mem_address);
        int32_t sign_ext_byte = pull_byte_from_memory(Data_mem, dmem_index);
        rt = sign_ext_byte; 
        PC = next_PC;
        next_PC += 4;
    }
    else if(mem_address <= IMEMOFFSET + IMEMLENGTH && mem_address >= IMEMOFFSET){
        uint32_t imem_index = imem_address_to_index(mem_address);
        int32_t sign_ext_byte = pull_byte_from_memory(Instruction_mem, imem_index);
        rt = sign_ext_byte;
        PC = next_PC;
        next_PC += 4; 
    }
    else if(mem_address >= ADDR_GETC && mem_address < ADDR_GETC + 4){
        int32_t return_data = get_c();

        if(return_data != -1){
            if(mem_address == ADDR_GETC + 3){
                rt = return_data;
            }
            else{
                rt = 0;
            }
        }
        else{
            rt = -1;
        }
        PC = next_PC;
        next_PC += 4;
    }
    else{
        std::exit(Memory_Exception);
    }
    
    return 0; 
}

instruction_rc LBU(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC,std::vector<uint8_t> Data_mem, std::vector<uint8_t> Instruction_mem){
    int32_t sign_ext_offset = offset;
    int32_t mem_address = base + sign_ext_offset; 

    if(mem_address <= DMEMOFFSET + DMEMLENGTH && mem_address >= DMEMOFFSET){
        uint32_t dmem_index = dmem_address_to_index(mem_address);
        uint32_t sign_ext_byte = pull_byte_from_memory(Data_mem, dmem_index);
        rt = sign_ext_byte & 0x000000FF; 
        PC = next_PC;
        next_PC += 4;
    }
    else if(mem_address <= IMEMOFFSET + IMEMLENGTH && mem_address >= IMEMOFFSET){
        uint32_t imem_index = imem_address_to_index(mem_address);
        uint32_t sign_ext_byte = pull_byte_from_memory(Instruction_mem, imem_index);
        rt = sign_ext_byte & 0x000000FF;
        PC = next_PC;
        next_PC += 4; 
    }
    else if(mem_address >= ADDR_GETC && mem_address < ADDR_GETC + 4){
        uint32_t return_data = get_c();

        if(return_data != -1){
            if(mem_address == ADDR_GETC + 3){
                rt = return_data & 0x000000FF;
            }
            else{
                rt = 0;
            }
        }
        else{
            rt = -1 && 0x000000FF;
        }
        PC = next_PC;
        next_PC += 4;
    }
    else{
        std::exit(Memory_Exception);
    }
    
    return 0; 
}

instruction_rc LH(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC,std::vector<uint8_t> Data_mem, std::vector<uint8_t> Instruction_mem){
    int32_t sign_ext_offset = offset;
    int32_t mem_address = base + sign_ext_offset; 

    if(mem_address % 2 == 0){
        if(mem_address < DMEMOFFSET + DMEMLENGTH && mem_address >= DMEMOFFSET){
            uint32_t dmem_index = dmem_address_to_index(mem_address);
            int16_t half_word16 = pull_hword_from_memory(Data_mem, dmem_index);
            int32_t half_word = half_word16;


            rt = half_word;
            PC = next_PC;
            next_PC += 4; 
        }
        else if(mem_address < IMEMOFFSET + IMEMLENGTH && mem_address >= IMEMOFFSET){
            uint32_t imem_index = imem_address_to_index(mem_address);
            int32_t half_word = pull_hword_from_memory(Instruction_mem, imem_index);
            rt = half_word;
            PC = next_PC;
            next_PC += 4; 
        }
        else if(mem_address >= ADDR_GETC && mem_address < ADDR_GETC + 4){
            int32_t return_data = get_c();

            if(return_data != -1){
                if(mem_address == ADDR_GETC + 2){
                    rt = return_data;
                }
                else{
                    rt = 0;
                }
            }
            else{
                rt = -1;
            }
            PC = next_PC;
            next_PC += 4;
        }
    }
    else{
        std::exit(Memory_Exception);
    }
    
    return 0;
}

instruction_rc LHU(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC,std::vector<uint8_t> Data_mem, std::vector<uint8_t> Instruction_mem){
    int32_t sign_ext_offset = offset;
    int32_t mem_address = base + sign_ext_offset; 

    if(mem_address % 2 == 0){
        if(mem_address < DMEMOFFSET + DMEMLENGTH && mem_address >= DMEMOFFSET){
            uint32_t dmem_index = dmem_address_to_index(mem_address);
            int32_t half_word = pull_hword_from_memory(Data_mem, dmem_index);
            rt = half_word & 0x0000FFFF;
            PC = next_PC;
            next_PC += 4; 
        }
        else if(mem_address < IMEMOFFSET + IMEMLENGTH && mem_address >= IMEMOFFSET){
            uint32_t imem_index = imem_address_to_index(mem_address);
            int32_t half_word = pull_hword_from_memory(Instruction_mem, imem_index);
            rt = half_word & 0x0000FFFF;
            PC = next_PC;
            next_PC += 4; 
        }
        else if(mem_address >= ADDR_GETC && mem_address < ADDR_GETC + 4){
            int32_t return_data = get_c();

            if(return_data != -1){
                if(mem_address == ADDR_GETC + 2){
                    rt = return_data & 0x000000FF;
                }
                else{
                    rt = 0;
                }
            }
            else{
                rt = -1 & 0x0000FFFF;
            }
            PC = next_PC;
            next_PC += 4;
        }
    }
    else{
        std::exit(Memory_Exception);
    }
    
    return 0;    
}

instruction_rc LUI(int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC){
    rt = (immediate << 16) & 0xFFFF0000;
    PC = next_PC;
    next_PC += 4;

}

instruction_rc LW(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC, std::vector<uint8_t> Data_mem, std::vector<uint8_t> Instruction_mem){
    int32_t sign_ext_offset = offset;
    int32_t mem_address = base + sign_ext_offset; 
    if(mem_address % 4 == 0){
        if(mem_address < DMEMOFFSET + DMEMLENGTH && mem_address >= DMEMOFFSET){

            uint32_t dmem_index = dmem_address_to_index(mem_address);
            int32_t word = pull_word_from_memory(Data_mem, dmem_index);

            rt = word;
            PC = next_PC;
            next_PC += 4; 
        }
        else if(mem_address < IMEMOFFSET + IMEMLENGTH && mem_address >= IMEMOFFSET){
            uint32_t imem_index = imem_address_to_index(mem_address);
            int32_t word = pull_word_from_memory(Instruction_mem, imem_index);
            rt = word;
            PC = next_PC;
            next_PC += 4; 
        }
        else if(mem_address >= ADDR_GETC && mem_address < ADDR_GETC + 4){
            if(mem_address == ADDR_GETC){
                int32_t return_data = get_c();
                rt = return_data;
                PC = next_PC;
                next_PC += 4;
            }
            else{
                std::exit(Memory_Exception);
            }
        }
        else{
            std::exit(Memory_Exception);
        }
    }
    else{
        std::exit(Memory_Exception);
    }
    
    return 0;    
}

instruction_rc LWL(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC, std::vector<uint8_t> Data_mem, std::vector<uint8_t> Instruction_mem){
    int32_t sign_ext_offset = offset;
    int32_t mem_address = base + sign_ext_offset;
    if(mem_address < DMEMOFFSET + DMEMLENGTH && mem_address >= DMEMOFFSET){
        uint32_t dmem_index = dmem_address_to_index(mem_address);
        lwl_helper(Data_mem, dmem_index, rt, mem_address);
        PC = next_PC;
        next_PC += 4; 
    }
    else if(mem_address < IMEMOFFSET + IMEMLENGTH && mem_address >= IMEMOFFSET){
        uint32_t imem_index = imem_address_to_index(mem_address);
        lwl_helper(Instruction_mem, imem_index, rt, mem_address);
        PC = next_PC;
        next_PC += 4; 
    }
    else if(mem_address >= ADDR_GETC && mem_address < ADDR_GETC + 4){
        int32_t Char_in = get_c();
        if(mem_address % 4 == 0){
            rt = Char_in;
        }
        else if(mem_address % 4 == 1){
            if(Char_in == -1){
                rt = (rt | 0xFFFFFF00);
            }
            else{
                rt = (rt & 0xFF) + ((Char_in & 0x00FFFFFF) << 8);
            }
        }
        else if(mem_address % 4 == 2){
            if(Char_in == -1){
                rt = (rt | 0xFFFF0000);
            }
            else{
                rt = (rt & 0xFFFF) + ((Char_in & 0x0000FFFF) << 16);
            }
        }
        else{
            if(Char_in == -1){
                rt = (rt | 0xFF000000);
            }
            else{
                rt = (rt & 0xFFFFFF) + ((Char_in & 0xFF) << 24);
            }
        }
        PC = next_PC;
        next_PC += 4; 
    }
    else{
        std::exit(Memory_Exception);
    }

    return 0;

}

// instruction_rc LWR(){}

instruction_rc MFHI(int32_t &rd, uint32_t &PC, uint32_t &next_PC, const int32_t &HI){

    rd = HI;

    PC = next_PC;
    next_PC += 4;

    return 0;
}

instruction_rc MFLO(int32_t &rd, uint32_t &PC, uint32_t &next_PC, const int32_t &LO){

    rd = LO;

    PC = next_PC;
    next_PC += 4;

    return 0;
}

instruction_rc MTHI(const int32_t &rs, uint32_t &PC, uint32_t &next_PC, int32_t &HI){

    HI = rs;

    PC = next_PC;
    next_PC += 4;

    return 0;
}

instruction_rc MTLO(const int32_t &rs, uint32_t &PC, uint32_t &next_PC, int32_t &LO){

    LO = rs;

    PC = next_PC;
    next_PC += 4;

    return 0;
}

instruction_rc MULT(const int32_t &rs, const int32_t &rt, uint32_t &PC, uint32_t &next_PC, int32_t &HI, int32_t &LO){ // check signed func
    int64_t product = rs * rt; 

    HI = product & 0xFFFFFFFF00000000;
    LO = product & 0xFFFFFFFF;

    PC = next_PC;
    next_PC += 4;

    return 0; 
}

instruction_rc MULTU(const int32_t &rs, const int32_t &rt, uint32_t &PC, uint32_t &next_PC, int32_t &HI, int32_t &LO){
    uint32_t unsigned_rs = rs;
    uint32_t unsigned_rt = rt;
    uint64_t product = unsigned_rs * unsigned_rt; 

    HI = product & 0xFFFFFFFF00000000;
    LO = product & 0xFFFFFFFF;

    PC = next_PC;
    next_PC += 4;

    return 0; 
}

instruction_rc OR(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC){
    rd = rs | rt;

    PC = next_PC;
    next_PC += 4;

    return 0;

}

instruction_rc ORI(const int32_t &rs, int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC){
    uint32_t zero_ext_offset = immediate;

    rt = rs | zero_ext_offset;

    PC = next_PC;
    next_PC += 4;

    return 0; 

}

instruction_rc SLL(const uint32_t &sa, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC){
    rd = rt << sa;

    PC = next_PC;
    next_PC += 4;

    return 0; 

}

instruction_rc SLLV(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC){
    uint8_t shift_amount = rs & 0x1F;

    rd = rt << shift_amount;

    PC = next_PC;
    next_PC += 4;

    return 0;

}

instruction_rc SLT(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC){
    if(rs < rt){
        rd = 1;
    }
    else{
        rd = 0; 
    }

    PC = next_PC;
    next_PC += 4;

    return 0;

}

instruction_rc SLTI(const int32_t &rs, int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC){
    int32_t sign_ext_imm = immediate;

    if(rs < sign_ext_imm){
        rt = 1;
    }
    else{
        rt = 0;
    }

    PC = next_PC;
    next_PC += 4;

    return 0;

}

instruction_rc SLTIU(const int32_t &rs, int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC){
    int32_t sign_ext_imm = immediate;
    uint32_t unsigned_imm = sign_ext_imm; 

    uint32_t unsigned_rs = rs;

    if(unsigned_rs < unsigned_imm){
        rt = 1;
    }
    else{
        rt = 0;
    }

    PC = next_PC;
    next_PC += 4;

    return 0;

}

instruction_rc SLTU(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC){
    uint32_t unsigned_rs = rs;
    uint32_t unsigned_rt = rt;
    
    if(unsigned_rs < unsigned_rt){
        rd = 1;
    }
    else{
        rd = 0; 
    }

    PC = next_PC;
    next_PC += 4;

    return 0;

}

instruction_rc SRA(const int32_t &sa, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC){
    rd = rt >> sa; 
    
    PC = next_PC;
    next_PC += 4;

    return 0;

}

instruction_rc SRAV(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC){
    uint8_t shift_amount = rs & 0x1F;

    rd = rt >> shift_amount; 

    PC = next_PC;
    next_PC += 4;

    return 0;    

}

instruction_rc SRL(const int32_t &sa, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC){
    uint32_t unsigned_rt = rt;
    unsigned_rt = unsigned_rt >> sa;

    rd = unsigned_rt; 

    PC = next_PC;
    next_PC += 4;

    return 0;

}

instruction_rc SRLV(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC){
    uint8_t shift_amount = rs & 0x1F;
    uint32_t unsigned_rt = rt;
    unsigned_rt = unsigned_rt >> shift_amount;

    rd = unsigned_rt; 

    PC = next_PC;
    next_PC += 4;

    return 0;

}

instruction_rc SUB(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC){
    if((rs < 0) && (rt >= 0) && (rs - rt >= 0)){
        std::exit(Arithmetic_Exception);
    }
    else if((rs >= 0) && (rt < 0) && (rs - rt < 0)){
        std::exit(Arithmetic_Exception);
    }
    else{
        rd =  rs - rt;
        PC = next_PC;
        next_PC += 4;
    }

    return 0;
}

instruction_rc SUBU(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC){
    rd =  rs - rt;
    PC = next_PC;
    next_PC += 4;

    return 0;

}

instruction_rc SW(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC, std::vector<uint8_t>& Data_mem){
    int32_t sign_ext_offset = offset;
    int32_t mem_address = base + sign_ext_offset; 
    if(mem_address % 4 == 0){
        if(mem_address < DMEMOFFSET + DMEMLENGTH && mem_address >= DMEMOFFSET){
            uint32_t index = dmem_address_to_index(mem_address);
            store_word_to_memory(Data_mem, index, rt);
                        
            PC = next_PC;
            next_PC += 4;
        }
        else if(mem_address >= ADDR_PUTC && mem_address <= ADDR_PUTC + 3){
            if(mem_address == ADDR_PUTC){
                std::putchar(rt);
                PC = next_PC;
                next_PC += 4;
            }
            else{
                std::exit(Memory_Exception);
            }
            
        }
        else{
            std::exit(Memory_Exception);
        }
    }
    else{
        std::exit(Memory_Exception);
    }

    return 0;
}

instruction_rc SB(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC, std::vector<uint8_t>& Data_mem){
    int32_t sign_ext_offset = offset;
    int32_t mem_address = base + sign_ext_offset;
    
    if(mem_address < DMEMOFFSET + DMEMLENGTH && mem_address >= DMEMOFFSET){
        uint32_t index = dmem_address_to_index(mem_address);
        Data_mem[index] = rt & 0x000000FF;
        PC = next_PC;
        next_PC += 4;
    }
    else if(mem_address >= ADDR_PUTC && mem_address <= ADDR_PUTC + 3){
        if(mem_address == ADDR_PUTC + 3){
            std::putchar(rt);
        }
        else{
            std::putchar(0);
        }

        PC = next_PC;
        next_PC += 4;
    }
    else{
        std::exit(Memory_Exception);
    }

    return 0; 
}

instruction_rc SH(const int32_t &base, int32_t &rt, const int16_t &offset, uint32_t &PC, uint32_t &next_PC, std::vector<uint8_t>& Data_mem){
    int32_t sign_ext_offset = offset;
    int32_t mem_address = base + sign_ext_offset; 

    if(mem_address % 2 == 0){
        if(mem_address < DMEMOFFSET + DMEMLENGTH && mem_address >= DMEMOFFSET){
            uint32_t index = dmem_address_to_index(mem_address);
            store_hword_to_memory(Data_mem, index, rt);
            PC = next_PC;
            next_PC += 4;
        }
        else if(mem_address >= ADDR_PUTC && mem_address <= ADDR_PUTC + 3){
            if(mem_address == ADDR_PUTC + 2){
                std::putchar(rt);
            }
            else{
                std::putchar(0);
            }
            PC = next_PC;
            next_PC += 4;
        }
        else{
            std::exit(Memory_Exception);
        }
    }
    else{
        std::exit(Memory_Exception);
    }

    return 0; 
}

instruction_rc XOR(const int32_t &rs, const int32_t &rt, int32_t &rd, uint32_t &PC, uint32_t &next_PC){

    rd = rs ^ rt;

    PC = next_PC;
    next_PC += 4;

    return 0;
}

instruction_rc XORI(const int32_t &rs, int32_t &rt, const int16_t &immediate, uint32_t &PC, uint32_t &next_PC){
    uint32_t zero_ext_imm = immediate;

    rt = rs ^ zero_ext_imm;

    PC = next_PC;
    next_PC += 4;

    return 0;

}
