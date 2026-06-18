# sum of array [10, 20, 30, 40, 50]
# array is pre-loaded at addresses 200-204
# R0 = sum, R1 = temp value

LOADI R0, 0
LOAD R1, 200
ADD R0, R0, R1
LOAD R1, 201
ADD R0, R0, R1
LOAD R1, 202
ADD R0, R0, R1
LOAD R1, 203
ADD R0, R0, R1
LOAD R1, 204
ADD R0, R0, R1
STORE R0, 210
HALT
