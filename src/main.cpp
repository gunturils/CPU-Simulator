#include <iostream>

struct RegisterFile {
	int registers[8]; // represents having 8 general purpose registers
};

struct Memory {
	unsigned char data[256]; // represents 256 bytes of memory
	// each 'memory' location (0-255) is addressable by index
};

int main() {
	RegisterFile rf;

	Memory mem; 

	mem.data[0] = 42;
	mem.data[1] = 99;

	rf.registers[0] = mem.data[0]; // R0 has the value in memory location 0
	rf.registers[1] = mem.data[1]; // R1 has the value in memory location 1
	rf.registers[2] = rf.registers[0] + rf.registers[1];

	std::cout << "Memory[0]: " << (int)mem.data[0]  << std::endl;
	std::cout << "Memory[1]: " << (int)mem.data[1]  << std::endl;
	std::cout << "R0: " << rf.registers[0] << std::endl;
	std::cout << "R1: " << rf.registers[1] << std::endl;
	std::cout << "R2 = R0 + R1: " << rf.registers[2] << std::endl;

	return 0;
}
