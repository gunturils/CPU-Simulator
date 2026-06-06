// header files is where you declare your structs and functions so every
// file in the project knows they exist
#ifndef CPU_H
#define CPU_H 
// prevent the header from being included twice

#include <iostream>

// all opcodes
enum class Opcode {
	ADD,
	SUB,
	LOAD,
	LOADI,
	STORE,
	JMP,
	BEQ,
	HALT
};

// represents a CPU instruction
struct Instruction {
	Opcode op;
	int dest = 0;
	int src1 = 0;
	int src2 = 0;
	int imm = 0;
};

// represents the cpu registers
struct RegisterFile {
	int registers[8] = {0};
};

// represents computer memory
struct Memory {
	unsigned char data[256] = {0};
};

// represents the CPU state
struct CPU {
	RegisterFile rf; // registers
	Memory mem; // memory
	int pc = 0; // initializes the program counter to 0
	bool halted = false; // flag that checks if the HALT instruction has been reached
};

// the following are function declarations that will be defined in cpu.cpp

Instruction fetch(CPU& cpu); // reads the next instruction in memory and increments pc

Instruction decode(unsigned char op, unsigned char dest, unsigned char src1, unsigned char src2); // turns the input byte into an instruction struct

void execute(CPU& cpu, Instruction instr); // carries out the instruction

void printReg(CPU& cpu); // prints the registers

void printInstr(Instruction instr); // prints a readable version of the instruction

#endif
