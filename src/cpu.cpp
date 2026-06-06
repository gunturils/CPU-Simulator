#include "../include/cpu.h"

Instruction fetch(CPU& cpu) {
	unsigned char op = cpu.mem.data[cpu.pc]; // first byte is the opcode
	unsigned char dest = cpu.mem.data[cpu.pc + 1]; // second byte is the destination register
	unsigned char src1 = cpu.mem.data[cpu.pc + 2]; // third byte is the first source register
	unsigned char src2 = cpu.mem.data[cpu.pc + 3]; // fourth byte is the last source register

	// move program counter by 4 to get the next instruction bc they are now 4 bytes each
	cpu.pc += 4;

	// pass all four bytes to decode
	return decode(op, dest, src1, src2);
}

// decode - turns byte of memory into readable instruction struct
Instruction decode(unsigned char op, unsigned char dest, unsigned char src1, unsigned char src2) {
	Instruction instr; // creates an empty instruction

	instr.dest = (int)dest; // sets dest reg as dest register
	instr.src1 = (int)src1; // sets src1 to int of src1
	instr.src2 = (int)src2; // sets src2 to int of src2
	instr.imm = (int)src2; // if there is an immediate being used it would be the last byte of the instruction

	switch (op) {
		// checks raw byte and assigns the matching opcode
		case 0: instr.op = Opcode::ADD; break;
		case 1: instr.op = Opcode::SUB; break;
		case 2: instr.op = Opcode::LOAD; break;
		case 3: instr.op = Opcode::LOADI; break;
		case 4: instr.op = Opcode::STORE; break;
		case 5: instr.op = Opcode::JMP; break;
		case 6: instr.op = Opcode::BEQ; break;
		case 7: instr.op = Opcode::HALT; break;
		default: instr.op = Opcode::HALT; break;
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
			cpu.rf.registers[instr.dest] = cpu.mem.data[instr.imm];
			break;
		case Opcode::LOADI:
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
                                << ", [" << instr.imm << "]" << std::endl;
                        break;
		case Opcode::LOADI:
			std::cout << "LOADI R" << instr.dest << ", " << instr.imm << std::endl;
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







