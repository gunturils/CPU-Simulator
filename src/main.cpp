#include <iostream>

struct RegisterFile {
	int registers[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // represents having 8 general purpose registers
};

struct Memory {
	unsigned char data[256]; // represents 256 bytes of memory
	// each 'memory' location (0-255) is addressable by index
};

void load(RegisterFile& rf, Memory& mem, int reg, int add) {
	rf.registers[reg] = mem.data[add];
}

void add(RegisterFile& rf, int dest, int src1, int src2) {
	rf.registers[dest] = rf.registers[src1] + rf.registers[src2];
}

void printReg(RegisterFile& rf) {
	for (int i = 0; i < 8; i++) {
		std::cout << "R" << i << ": " << rf.registers[i] << std::endl;
	}
}

int main() {
	RegisterFile rf;

	Memory mem; 

	mem.data[0] = 42;
	mem.data[1] = 99;

	load(rf, mem, 0, 0); // loads memory byte 0 into R0
	load(rf, mem, 1, 1); // loads memory byte 1 into R1
	add(rf, 2, 0, 1); // loads R0+R1 into R2
	
	printReg(rf);

	return 0;
}

