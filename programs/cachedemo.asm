# demonstrates cache hits by reading same addresses repeatedly
# first pass — all misses, loads into cache
LOAD R0, 200
LOAD R1, 201
# second pass — all hits, data already in cache
LOAD R2, 200
LOAD R3, 201
# third pass — more hits
LOAD R4, 200
LOAD R5, 201
HALT
