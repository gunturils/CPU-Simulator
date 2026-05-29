#include "../include/cpu.h"

int main() {
	CPU cpu; // initializes a cpu instance

	cpu.mem.data[0] = 2; // address 0 -> LOAD instruction (opcode 2)
	cpu.mem.data[1] = 0; // address 1 -> ADD instruction (opcode 0)
	cpu.mem.data[2] = 6; // address 2 -> HALT instruction (opcode 6)

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
