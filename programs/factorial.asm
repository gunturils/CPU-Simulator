# factorial of 5
# R0 = counter (starts at 5)
# R1 = running product (starts at 1)
# R2 = decrement value (1)
# R3 = stop condition (0)

LOADI R0, 5
LOADI R1, 1
LOADI R2, 1
LOADI R3, 0

# loop starts here at address 16
MUL R1, R1, R0
SUB R0, R0, R2
BEQ R0, R3, 36
JMP 16

# store result and halt at address 36
STORE R1, 200
HALT
