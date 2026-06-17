# CPU Simulator

A custom CPU simulator built from scratch in C++, featuring a fully designed Instruction Set Architecture (ISA), an assembler, and an interactive web-based UI. Built as a deep dive into computer architecture fundamentals.

---

## Demo

Open `ui/index.html` in any browser to use the interactive simulator — write assembly code, step through instructions, and watch registers and memory update in real time.

---

## Features

- **Custom ISA** — 10 instructions designed from scratch (ADD, SUB, MUL, LOAD, LOADI, LOADR, STORE, JMP, BEQ, HALT)
- **Fetch → Decode → Execute pipeline** — mirrors the architecture of real CPUs
- **8 general purpose registers** and 256 bytes of addressable memory
- **4-byte instruction encoding** — each instruction encodes opcode, destination register, source registers, and immediate value
- **Assembler** — converts human-readable `.asm` files directly into machine code loaded into the simulator
- **Performance counter** — tracks total instructions executed per program
- **Interactive UI** — browser-based interface with line highlighting, register visualization, and memory inspection
- **Step-through debugger** — execute one instruction at a time and watch the CPU state update live

---

## Architecture

### Instruction Set

| Instruction | Format | Description |
|---|---|---|
| `ADD` | `ADD Rd, Rs1, Rs2` | Rd = Rs1 + Rs2 |
| `SUB` | `SUB Rd, Rs1, Rs2` | Rd = Rs1 - Rs2 |
| `MUL` | `MUL Rd, Rs1, Rs2` | Rd = Rs1 × Rs2 |
| `LOAD` | `LOAD Rd, addr` | Rd = Memory[addr] |
| `LOADI` | `LOADI Rd, imm` | Rd = imm |
| `LOADR` | `LOADR Rd, Rs` | Rd = Memory[Rs] |
| `STORE` | `STORE Rs, addr` | Memory[addr] = Rs |
| `JMP` | `JMP addr` | PC = addr |
| `BEQ` | `BEQ Rs1, Rs2, addr` | if Rs1 == Rs2: PC = addr |
| `HALT` | `HALT` | Stop execution |

### Instruction Encoding

Each instruction is **4 bytes wide**:

### Fetch → Decode → Execute

---

## Project Structure

---

## Getting Started

### Requirements

- Linux or macOS
- `g++` (C++17 or later)
- `make`
- Python 3 (for the assembler)

### Build

```bash
make
```

### Run a program

```bash
./simulator programs/factorial.asm
```

### Use the assembler

```bash
python3 assembler.py programs/factorial.asm
```

### Use the UI

Open `ui/index.html` in any browser. No server required.

---

## Example Programs

### Factorial of 5

```asm
# computes 5! = 120
# R0 = counter, R1 = product, R2 = decrement, R3 = stop condition

LOADI R0, 5
LOADI R1, 1
LOADI R2, 1
LOADI R3, 0
MUL R1, R1, R0
SUB R0, R0, R2
BEQ R0, R3, 32
JMP 16
STORE R1, 200
HALT
```

**Result:** R1 = 120, stored at memory address 200.

### Sum of Array

```asm
# sums [10, 20, 30, 40, 50] stored at addresses 200-204
# R0 = pointer, R1 = sum, R2 = end address, R3 = increment, R4 = current element

LOADI R0, 200
LOADI R1, 0
LOADI R2, 205
LOADI R3, 1
LOADR R4, R0
ADD R1, R1, R4
ADD R0, R0, R3
BEQ R0, R2, 40
JMP 16
STORE R1, 210
HALT
```

**Result:** R1 = 150, stored at memory address 210.

---

## What I Learned

- How the fetch-decode-execute cycle works at the hardware level
- How ISAs encode instructions as binary and why instruction width matters
- How programs are laid out in memory and how the program counter tracks execution
- How branching and jumping work at the hardware level — the foundation of loops and conditionals
- How to build a working assembler that translates human-readable code to machine code
- C++ systems programming: structs, enums, pointers, file I/O, Makefiles, and multi-file projects

---

## Built With

- **C++** — core simulator
- **Python** — assembler
- **HTML / CSS / JavaScript** — interactive UI

---

*Built as part of a self-directed computer architecture study plan — May/June 2026*
