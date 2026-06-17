#include "../include/cpu.h"
#include <fstream>
// fstream lets us read files
#include <sstream>
// sstream lets us parse strings
#include <string>
// string lets us work with text

// opcode lookup — maps instruction name to numeric opcode
// must match exactly what decode() expects
int getOpcode(const std::string& op) {
    if (op == "ADD")   return 0;
    if (op == "SUB")   return 1;
    if (op == "MUL")   return 2;
    if (op == "LOAD")  return 3;
    if (op == "LOADI") return 4;
    if (op == "STORE") return 5;
    if (op == "JMP")   return 6;
    if (op == "BEQ")   return 7;
    if (op == "HALT")  return 8;
    return 8;
    // default to HALT if unknown
}

// register lookup — maps "R0" to 0, "R1" to 1, etc.
int getReg(const std::string& reg) {
    // remove commas that might be attached
    std::string r = reg;
    if (!r.empty() && r.back() == ',') r.pop_back();
    // pop_back removes the last character
    return std::stoi(r.substr(1));
    // substr(1) removes the "R" prefix
    // stoi converts the remaining number string to int
}

// loads an assembly file directly into CPU memory
void loadProgram(CPU& cpu, const std::string& filename) {
    std::ifstream file(filename);
    // opens the file for reading
    if (!file.is_open()) {
        std::cout << "Error: could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    // holds each line as we read it
    int address = 0;
    // tracks current memory address

    while (std::getline(file, line)) {
        // getline reads one line at a time

        // skip empty lines and comments
        if (line.empty() || line[0] == '#') continue;

        // remove inline comments
        size_t commentPos = line.find('#');
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
            // cut off everything after #
        }

        std::istringstream iss(line);
        // istringstream lets us parse the line word by word
        std::string op;
        iss >> op;
        // read the first word (the opcode)

        if (op.empty()) continue;
        // skip lines that are only whitespace

        // convert to uppercase
        for (auto& c : op) c = toupper(c);

        int opcode = getOpcode(op);

        if (op == "HALT") {
            cpu.mem.data[address++] = opcode;
            cpu.mem.data[address++] = 0;
            cpu.mem.data[address++] = 0;
            cpu.mem.data[address++] = 0;
            // HALT has no arguments

        } else if (op == "ADD" || op == "SUB" || op == "MUL") {
            std::string dest, src1, src2;
            iss >> dest >> src1 >> src2;
            cpu.mem.data[address++] = opcode;
            cpu.mem.data[address++] = getReg(dest);
            cpu.mem.data[address++] = getReg(src1);
            cpu.mem.data[address++] = getReg(src2);

        } else if (op == "LOADI" || op == "LOAD") {
            std::string dest, imm;
            iss >> dest >> imm;
            cpu.mem.data[address++] = opcode;
            cpu.mem.data[address++] = getReg(dest);
            cpu.mem.data[address++] = 0;
            cpu.mem.data[address++] = std::stoi(imm);

        } else if (op == "STORE") {
            std::string src1, imm;
            iss >> src1 >> imm;
            cpu.mem.data[address++] = opcode;
            cpu.mem.data[address++] = getReg(src1);
            cpu.mem.data[address++] = 0;
            cpu.mem.data[address++] = std::stoi(imm);

        } else if (op == "JMP") {
            std::string imm;
            iss >> imm;
            cpu.mem.data[address++] = opcode;
            cpu.mem.data[address++] = 0;
            cpu.mem.data[address++] = 0;
            cpu.mem.data[address++] = std::stoi(imm);

        } else if (op == "BEQ") {
            std::string src1, src2, imm;
            iss >> src1 >> src2 >> imm;
            cpu.mem.data[address++] = opcode;
            cpu.mem.data[address++] = getReg(src1);
            cpu.mem.data[address++] = getReg(src2);
            cpu.mem.data[address++] = std::stoi(imm);
        }
    }

    file.close();
}

int main(int argc, char* argv[]) {
    // argc is the number of command line arguments
    // argv is the array of argument strings
    // argv[0] is always the program name
    // argv[1] is the first argument (our .asm file)

    if (argc < 2) {
        std::cout << "Usage: ./simulator <program.asm>" << std::endl;
        return 1;
    }

    CPU cpu;
    // create CPU

    loadProgram(cpu, argv[1]);
    // load the assembly file directly into memory

    std::cout << "--- Running: " << argv[1] << " ---" << std::endl;

    int instructionCount = 0;

    while (!cpu.halted) {
        Instruction instr = fetch(cpu);
        printInstr(instr);
        execute(cpu, instr);
        instructionCount++;
    }

    std::cout << "--- Registers after execution ---" << std::endl;
    printReg(cpu);

    std::cout << "--- Performance ---" << std::endl;
    std::cout << "Total instructions executed: " << instructionCount << std::endl;

    return 0;
}
