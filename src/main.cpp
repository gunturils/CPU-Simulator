#include "../include/cpu.h"

int main() {
	CPU cpu; // initializes a cpu instance

	cpu.mem.data[200] = 42;
	cpu.mem.data[201] = 99;

	cpu.mem.data[0] = 2; // address 0 -> LDR R0, R0, #200
	cpu.mem.data[1] = 0; // address 1 -> destination register is R0
	cpu.mem.data[2] = 0; // address 2 -> source register 1 is R0
	cpu.mem.data[3] = 200; // address 3 -> immediate is the memory address to load from

	cpu.mem.data[4] = 2; // address 0 -> LDR R1, R0, #201
        cpu.mem.data[5] = 1; // address 1 -> destination register is R1
        cpu.mem.data[6] = 0; // address 2 -> source register 1 is R0
        cpu.mem.data[7] = 201; // address 3 -> immediate is the memory address 

	cpu.mem.data[8] = 0; // address 0 -> ADD R2, R0, R1
        cpu.mem.data[9] = 2; // address 1 -> destination register is R2
        cpu.mem.data[10] = 0; // address 2 -> source register 1 is R0
        cpu.mem.data[11] = 1; // address 3 -> source register 2 is R1

	cpu.mem.data[12] = 6; // address 0 -> HALT
        cpu.mem.data[13] = 0; // address 1 -> unused
        cpu.mem.data[14] = 0; // address 2 -> unused
        cpu.mem.data[15] = 0; // address 3 -> unused

	std::cout << "--- Program ---" << std::endl;

	while (!cpu.halted) {
		Instruction instr = fetch(cpu);

		printInstr(instr);
		execute(cpu, instr);
	}

	std::cout << "--- Registers after execution ---" << std::endl;
	printReg(cpu);

	return 0;
}
