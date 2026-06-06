#include "../include/cpu.h"

int main() {
	CPU cpu; // initializes a cpu instance

	//cpu.mem.data[200] = 42;
	// cpu.mem.data[200] = 10;
	// cpu.mem.data[201] = 20;

	cpu.mem.data[0] = 3; // LOADI R0, #1
	cpu.mem.data[1] = 0;
	cpu.mem.data[2] = 0;
	cpu.mem.data[3] = 1;

	cpu.mem.data[4] = 3; // LOADI R1, #6
        cpu.mem.data[5] = 1;
        cpu.mem.data[6] = 0;
        cpu.mem.data[7] = 6;

	cpu.mem.data[8] = 3; // LOADI R2, #1
        cpu.mem.data[9] = 2;
        cpu.mem.data[10] = 0;
        cpu.mem.data[11] = 1;

	cpu.mem.data[12] = 4; // STR R0, [200]
	cpu.mem.data[13] = 0;
	cpu.mem.data[14] = 0;
	cpu.mem.data[15] = 200;

	cpu.mem.data[16] = 0; // ADD R0, R0, R2
	cpu.mem.data[17] = 0;
	cpu.mem.data[18] = 0;
	cpu.mem.data[19] = 2;

	cpu.mem.data[20] = 6; // BEQ R0, R1, 32
	cpu.mem.data[21] = 0;
	cpu.mem.data[22] = 1;
	cpu.mem.data[23] = 32;

	cpu.mem.data[24] = 6; // LOADI R4, #99
        cpu.mem.data[25] = 0;
        cpu.mem.data[26] = 0;
        cpu.mem.data[27] = 12;

        cpu.mem.data[28] = 7; // JMP 36 -> jump unconditionally to address 36
        cpu.mem.data[29] = 0;
        cpu.mem.data[30] = 0;
        cpu.mem.data[31] = 36;

        cpu.mem.data[32] = 7; // LOADI R4, #0
        cpu.mem.data[33] = 0;
        cpu.mem.data[34] = 0;
        cpu.mem.data[35] = 0;

	cpu.mem.data[36] = 7; //HALT
	cpu.mem.data[37] = 0;
	cpu.mem.data[38] = 0;
	cpu.mem.data[39] = 0;


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

	std::cout << "--- Memory after execution ---" << std::endl;
	std::cout << "mem[200]: " << (int)cpu.mem.data[200] << std::endl;
	// std::cout << "mem[201]: " << (int)cpu.mem.data[201] << std::endl;
	// std::cout << "mem[202]: " << (int)cpu.mem.data[202] << std::endl;

	std::cout << "--- Performance ---" << std::endl;
	std::cout << "Total instructions executed: " << instrCount << std::endl;

	return 0;
}
