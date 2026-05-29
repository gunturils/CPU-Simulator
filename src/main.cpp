#include <iostream>

enum class Opcode {
	ADD,
	SUB,
	LOAD,
	STORE, 
	JMP,
	BEQ,
	HALT
};

struct Instruction {
	Opcode op;
	int dest;
	int src1;
	int src2;
	int imm;
};

struct RegisterFile {
	int registers[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // represents having 8 general purpose registers
};

struct Memory {
	unsigned char data[256]; // represents 256 bytes of memory
	// each 'memory' location (0-255) is addressable by index
};

void printInstruction(Instruction instr) {
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

void printRegisters(RegisterFile& rf) {
	for (int i = 0; i < 8; i++) {
		std::cout << "R" << i << ": " << rf.registers[i] << std::endl;
	}
}

int main() {
	Instruction instr1; //creates instruction variable called instr1
	instr1.op = Opcode::LOAD;
	instr1.dest = 0;
	instr1.imm = 42;

	Instruction instr2;
	instr2.op = Opcode::ADD;
	instr2.dest = 2;
	instr2.src1 = 0;
	instr2.src2 = 1;

	Instruction instr3;
	instr3.op = Opcode::HALT;

	printInstruction(instr1); // verifies that the instructions are printing correctly
	printInstruction(instr2);
	printInstruction(instr3);

	return 0;
}

