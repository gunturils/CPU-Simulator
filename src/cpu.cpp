#include "../include/cpu.h"

Instruction fetch(CPU& cpu) {
	// reates the byte at the current pc location
	unsigned char byte = cpu.mem.data[cpu.pc];

	cpu.pc++; // increments pc

	return decode(byte);
}

// decode - turns byte of memory into readable instruction struct
Instruction decode(unsigned char byte) {
	Instruction instr; // creates an empty instruction

	switch (byte) {
		// checks raw byte and assigns the matching opcode
		case 0: instr.op = Opcode::ADD; break;
		case 1: instr.op = Opcode::SUB; break;
		case 2: instr.op = Opcode::LOAD; break;
		case 3: instr.op = Opcode::STORE; break;
		case 4: instr.op = Opcode::JMP; break;
		case 5: instr.op = Opcode::BEQ; break;
		case 6: instr.op = Opcode::HALT; break;
		default: instr.op = Opcode::HALT;
	}
	return instr;
}

// execute - looks at the instruction and carries out the right operation
void execute(CPU&  cpu, Instruction instr) {
	switch (instr.op) {
		case Opcode::ADD:
			cpu.rf.registers[instr.dest] =
			cpu.rf.registers[instr.src1] + cpu.rf.registers[instr.src2];
			break;
		case Opcode::SUB:
			cpu.rf.registers[instr.dest] = 
			cpu.rf.registers[instr.src1] - cpu.rf.registers[instr.src2];
			break;
		case Opcode::LOAD:
			cpu.rf.registers[instr.dest] = instr.imm;
			break;
		case Opcode::STORE:
			cpu.mem.data[instr.imm] = cpu.rf.registers[instr.src1];
			break;
		case Opcode::JMP:
			cpu.pc = instr.imm;
			break;
		case Opcode::BEQ:
			if (cpu.rf.registers[instr.src1] == cpu.rf.registers[instr.src2]) {
				cpu.pc = instr.imm;
			}
			break;
		case Opcode::HALT:
			cpu.halted = true;
			break;
	}
}

// printReg - prints all 8 registers
void printReg(CPU& cpu) {
	for (int i = 0; i < 8; i++) {
		std::cout << "R" << i << ": " << cpu.rf.registers[i] << std::endl;
	}
}

// prints a human readable version of an instruction
void printInstr(Instruction instr) {
        switch (instr.op) {
                case Opcode::ADD:
                        std::cout << "ADD R" << instr.dest
                                << ", R" << instr.src1
                                << ", R" << instr.src2 << std::endl;
                        break;
                case Opcode::SUB:
                        std::cout << "SUB R" << instr.dest
                                << ", R" << instr.src1
                                << ", R" << instr.src2 << std::endl;
                        break;
                case Opcode::LOAD:
                        std::cout << "LOAD R" << instr.dest
                                << ", " << instr.imm << std::endl;
                        break;
                case Opcode::STORE:
                        std::cout << "STORE R" << instr.src1
                                << ", " << instr.imm << std::endl;
                        break;
                case Opcode::JMP:
                        std::cout << "JMP " << instr.imm << std::endl;
                        break;
                case Opcode::BEQ:
                        std::cout << "BEQ R" << instr.src1
                                << ", R" << instr.src2
                                << ", " << instr.imm << std::endl;
                        break;
                case Opcode::HALT:
                        std::cout << "HALT" << std::endl;
                        break;
        }
}







