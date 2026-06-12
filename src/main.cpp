#include "../include/cpu.h"

int main() {
	CPU cpu; // initializes a cpu instance

	//cpu.mem.data[200] = 42;
	// cpu.mem.data[200] = 10;
	// cpu.mem.data[201] = 20;

	cpu.mem.data[0] = 4; // LOADI R0, #1
	cpu.mem.data[1] = 0;
	cpu.mem.data[2] = 0;
	cpu.mem.data[3] = 5;

	cpu.mem.data[4] = 4; // LOADI R1, #6
        cpu.mem.data[5] = 1;
        cpu.mem.data[6] = 0;
        cpu.mem.data[7] = 1;

	cpu.mem.data[8] = 4; // LOADI R2, #1
        cpu.mem.data[9] = 2;
        cpu.mem.data[10] = 0;
        cpu.mem.data[11] = 1;

	cpu.mem.data[12] = 4; // STR R0, [200]
	cpu.mem.data[13] = 3;
	cpu.mem.data[14] = 0;
	cpu.mem.data[15] = 0;

	cpu.mem.data[16] = 2; // ADD R0, R0, R2
	cpu.mem.data[17] = 1;
	cpu.mem.data[18] = 1;
	cpu.mem.data[19] = 0;

	cpu.mem.data[20] = 1; // BEQ R0, R1, 32
	cpu.mem.data[21] = 0;
	cpu.mem.data[22] = 0;
	cpu.mem.data[23] = 2;

	cpu.mem.data[24] = 7; // LOADI R4, #99
        cpu.mem.data[25] = 0;
        cpu.mem.data[26] = 3;
        cpu.mem.data[27] = 32;

        cpu.mem.data[28] = 6; // JMP 36 -> jump unconditionally to address 36
        cpu.mem.data[29] = 0;
        cpu.mem.data[30] = 0;
        cpu.mem.data[31] = 16;

        cpu.mem.data[32] = 5; // LOADI R4, #0
        cpu.mem.data[33] = 1;
        cpu.mem.data[34] = 0;
        cpu.mem.data[35] = 200;

	cpu.mem.data[36] = 8; //HALT
	cpu.mem.data[37] = 0;
	cpu.mem.data[38] = 0;
	cpu.mem.data[39] = 0;

	std::cout << "--- Program: Factorial of 5 ---" << std::endl;

	int instrCount = 0;

	std::cout << "--- Program ---" << std::endl;

	while (!cpu.halted) {
		Instruction instr = fetch(cpu);
		printInstr(instr);
		execute(cpu, instr);
		instrCount++;
	}

	std::cout << "--- Registers after execution ---" << std::endl;
	printReg(cpu);

	std::cout << "--- Result ---" << std::endl;
	std::cout << "5! = " << (int)cpu.mem.data[200] << std::endl;

	//std::cout << "--- Memory after execution ---" << std::endl;
	//std::cout << "mem[200]: " << (int)cpu.mem.data[200] << std::endl;
	// std::cout << "mem[201]: " << (int)cpu.mem.data[201] << std::endl;
	// std::cout << "mem[202]: " << (int)cpu.mem.data[202] << std::endl;

	std::cout << "--- Performance ---" << std::endl;
	std::cout << "Total instructions executed: " << instrCount << std::endl;

	return 0;
}
