#include "../include/cpu.h"

int main() {
	CPU cpu; // initializes a cpu instance

	//cpu.mem.data[200] = 42;
	cpu.mem.data[200] = 10;
	cpu.mem.data[201] = 20;

	cpu.mem.data[0] = 2; // address 0 -> LDR R0, R0, #200
	cpu.mem.data[1] = 0; // address 1 -> destination register is R0
	cpu.mem.data[2] = 0; // address 2 -> source register 1 is R0
	cpu.mem.data[3] = 200; // address 3 -> immediate is the memory address to load from

	cpu.mem.data[4] = 2; // address 0 -> LDR R1, R0, [201]
        cpu.mem.data[5] = 1; // address 1 -> destination register is R1
        cpu.mem.data[6] = 0; // address 2 -> source register 1 is R0
        cpu.mem.data[7] = 201; // address 3 -> immediate is the memory address 

	cpu.mem.data[8] = 0; // address 0 -> HALT
        cpu.mem.data[9] = 2; // address 1 -> unused
        cpu.mem.data[10] = 0; // address 2 -> unused
        cpu.mem.data[11] = 1; // address 3 -> unused

	cpu.mem.data[12] = 4; // STR R2, [202]
	cpu.mem.data[13] = 2;
	cpu.mem.data[14] = 0;
	cpu.mem.data[15] = 202;

	cpu.mem.data[16] = 3; // LOADI R3, #0
	cpu.mem.data[17] = 3;
	cpu.mem.data[18] = 0;
	cpu.mem.data[19] = 0;

	cpu.mem.data[20] = 6; // BEQ R0, R3, 36 -> If R0 == R3, jump to the address 36
	cpu.mem.data[21] = 0;
	cpu.mem.data[22] = 3;
	cpu.mem.data[23] = 36;

	cpu.mem.data[24] = 3; // LOADI R4, #99
        cpu.mem.data[25] = 4;
        cpu.mem.data[26] = 0;
        cpu.mem.data[27] = 99;

        cpu.mem.data[28] = 5; // JMP 36 -> jump unconditionally to address 36
        cpu.mem.data[29] = 0;
        cpu.mem.data[30] = 0;
        cpu.mem.data[31] = 36;

        cpu.mem.data[32] = 3; // LOADI R4, #0
        cpu.mem.data[33] = 4;
        cpu.mem.data[34] = 0;
        cpu.mem.data[35] = 0;

	cpu.mem.data[36] = 7; //HALT
	cpu.mem.data[37] = 0;
	cpu.mem.data[38] = 0;
	cpu.mem.data[39] = 0;


	std::cout << "--- Program ---" << std::endl;

	while (!cpu.halted) {
		Instruction instr = fetch(cpu);
		printInstr(instr);
		execute(cpu, instr);
	}

	std::cout << "--- Registers after execution ---" << std::endl;
	printReg(cpu);

	std::cout << "--- Memory after execution ---" << std::endl;
	std::cout << "mem[200]: " << (int)cpu.mem.data[200] << std::endl;
	std::cout << "mem[201]: " << (int)cpu.mem.data[201] << std::endl;
	std::cout << "mem[202]: " << (int)cpu.mem.data[202] << std::endl;

	return 0;
}
