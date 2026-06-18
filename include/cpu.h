#ifndef CPU_H
#define CPU_H

#include <iostream>

// ============================================================
// CACHE CONSTANTS
// ============================================================

#define CACHE_SIZE 8
// number of slots in the cache
#define MISS_PENALTY 10
// extra cycles added on every cache miss

// ============================================================
// CACHE STRUCTS — must be defined before CPU struct
// ============================================================

struct CacheSlot {
    bool valid = false;
    // false means this slot is empty
    int tag = -1;
    // which memory address this slot holds data from
    unsigned char data = 0;
    // the actual value stored in this slot
};

struct Cache {
    CacheSlot slots[CACHE_SIZE];
    // array of cache slots
    int hits = 0;
    // number of successful cache lookups
    int misses = 0;
    // number of failed cache lookups
    int totalCycles = 0;
    // total cycles including miss penalties
};

// ============================================================
// ISA
// ============================================================

enum class Opcode {
    ADD,    // addition
    SUB,    // subtraction
    MUL,    // multiplication
    LOAD,   // load from memory address into register
    LOADI,  // load immediate value directly into register
    STORE,  // store register value into memory
    JMP,    // jump to address
    BEQ,    // branch if equal
    HALT    // stop program
};

struct Instruction {
    Opcode op;
    int dest;
    int src1;
    int src2;
    int imm;
};

// ============================================================
// CPU COMPONENTS
// ============================================================

struct RegisterFile {
    int registers[8] = {0};
    // 8 general purpose registers initialized to 0
};

struct Memory {
    unsigned char data[256] = {0};
    // 256 bytes of memory initialized to 0
};

struct CPU {
    RegisterFile rf;
    Memory mem;
    int pc = 0;
    bool halted = false;
    Cache cache;
    // cache now defined above so CPU can reference it
};

// ============================================================
// FUNCTION DECLARATIONS
// ============================================================

// cpu.cpp
Instruction fetch(CPU& cpu);
Instruction decode(unsigned char op, unsigned char dest,
                   unsigned char src1, unsigned char src2);
void execute(CPU& cpu, Instruction instr);
void printReg(CPU& cpu);
void printInstr(Instruction instr);

// cache.cpp
unsigned char cacheRead(CPU& cpu, int address);
void cacheWrite(CPU& cpu, int address, unsigned char value);
void printCacheStats(CPU& cpu);
void printCacheContents(CPU& cpu);

#endif
