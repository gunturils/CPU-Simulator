# asm.py
# converts human readable assembly text into byte sequences

import sys
# allows us to run command line arguments

# opcode table
OPCODES = {
	"ADD": 0,
	"SUB": 1,
	"MUL": 2,
	"LOAD": 3,
	"LOADI": 4,
	"STORE": 5,
	"BEQ": 6,
	"JMP": 7,
	"HALT": 8,
}

# register table
REGISTERS = {
	"R0": 0,
	"R1": 1,
	"R2": 2,
	"R3": 3,
	"R4": 4,
	"R5": 5,
	"R6": 6,
	"R7": 7,
}

def parse_register(token):
	# takes a string like "R0" and returns the number 0
	# strips any commas
	token = token.strip().strip(",").upper()

	if token not in REGISTERS:
		print(f"Error: unknown register '{token}'")
		sys.exit(1)
	return REGISTERS[token]

def parse_imm(token):
	token = token.strip().strip(",")
	return int(token)

def assemble(filename):

	output = []

	with open(filename, "r") as f:
		lines = f.readlines()

	for line_enum, line in enumerate(lines):
		line = line.strip()

		if not line or line.startswith("#"):
			continue

		parts = line.split()

		opcode_str = parts[0].upper()

		if opcode_str not in OPCODES:
			print(f"Error on line {line_num + 1}: unknown instruction '{opcode_str}'") 
			sys.exit(1)

		opcode = OPCODES[opcode_str]

		if opcode_str == "HALT":
			output.extend([opcode, 0, 0, 0])

		elif opcode_str in ("ADD", "SUB", "MUL"):
			dest = parse_register(parts[1])
			src1 = parse_register(parts[2])
			src2 = parse_register(parts[3])
			output.extend([opcode, dest, src1, src2])

		elif opcode_str == "LOADI":
			dest = parse_register(parts[1])
			imm = parse_imm(parts[2])
			output.extend([opcode, dest, 0, imm])

		elif opcode_str == "LOAD":
			dest = parse_register(parts[1])
			imm = parse_imm(parts[2])
			output.extend([opcode, dest, 0, imm])

		elif opcode_str == "STORE":
			src1 = parse_register(parts[1])
			imm = parse_imm(parts[2])
			output.extend([opcode, src1, 0, imm])

		elif opcode_str == "JMP":
			imm = parse_imm(parts[1])
			output.extend([opcode, 0, 0, imm])

		elif opcode_str == "BEQ":
			src1 = parse_register(parts[1])
			src2 = parse_register(parts[2])
			imm = parse_imm(parts[3])
			output.extend([opcode, src1, src2, imm])

	return output

def main():
	if len(sys.argv) < 2:
		print("Usage: python3 assembler.py <program.asm?")
		sys.exit(1)

	filename = sys.argv[1]

	bytes_out = assemble(filename)

	print("# assembled output")
	print(f"# {len(bytes_out)} bytes total, {len(bytes_out) // 4} instructions")
	print()

	for i, val in enumerate(bytes_out):
		print(f"cpu.mem.data[{i}] = {val};")

main()
