#include "../include/cpu.h"

// READ FROM CACHE
// checks the cache before going to memory
// records hits and misses
unsigned char cacheRead(CPU& cpu, int address) {
    int slot = address % CACHE_SIZE;
    // calculate which cache slot this address maps to
    // direct mapped — every address has exactly one possible slot

    CacheSlot& entry = cpu.cache.slots[slot];
    // get a reference to that slot

    cpu.cache.totalCycles++;
    // every memory access costs at least 1 cycle

    if (entry.valid && entry.tag == address) {
        // CACHE HIT
        // the slot is valid AND the tag matches our address
        // this means the right data is already in cache
        cpu.cache.hits++;
        return entry.data;
        // return the cached value — no memory access needed
    }

    // CACHE MISS
    // either the slot was empty or it had data from a different address
    cpu.cache.misses++;
    cpu.cache.totalCycles += MISS_PENALTY;
    // pay the miss penalty — simulates going to slow main memory

    unsigned char value = cpu.mem.data[address];
    // fetch the value from main memory

    // bring the data into cache for next time
    entry.valid = true;
    entry.tag   = address;
    entry.data  = value;
    // update the slot with the new address and value

    return value;
}

// WRITE TO CACHE
// writes value to memory and updates cache if that address is cached
// this is called a write-through policy — always write to memory
void cacheWrite(CPU& cpu, int address, unsigned char value) {
    cpu.mem.data[address] = value;
    // always write through to main memory
    // this keeps memory and cache consistent

    int slot = address % CACHE_SIZE;
    CacheSlot& entry = cpu.cache.slots[slot];

    // if this address is already in cache, update it too
    if (entry.valid && entry.tag == address) {
        entry.data = value;
        // keep cache consistent with memory
    }

    cpu.cache.totalCycles++;
    // writes cost 1 cycle
}

// PRINT CACHE STATISTICS
void printCacheStats(CPU& cpu) {
    int total = cpu.cache.hits + cpu.cache.misses;
    // total number of cache accesses

    float hitRate = total > 0
        ? (float)cpu.cache.hits / total * 100.0f
        : 0.0f;
    // hit rate as a percentage
    // guard against division by zero if no accesses happened

    std::cout << "--- Cache Statistics ---" << std::endl;
    std::cout << "Cache size:     " << CACHE_SIZE << " slots" << std::endl;
    std::cout << "Total accesses: " << total << std::endl;
    std::cout << "Cache hits:     " << cpu.cache.hits << std::endl;
    std::cout << "Cache misses:   " << cpu.cache.misses << std::endl;
    std::cout << "Hit rate:       " << hitRate << "%" << std::endl;
    std::cout << "Total cycles:   " << cpu.cache.totalCycles << std::endl;
    std::cout << "Miss penalty:   " << MISS_PENALTY
              << " cycles per miss" << std::endl;
}

// PRINT CACHE CONTENTS
void printCacheContents(CPU& cpu) {
    std::cout << "--- Cache Contents ---" << std::endl;
    for (int i = 0; i < CACHE_SIZE; i++) {
        CacheSlot& slot = cpu.cache.slots[i];
        if (slot.valid) {
            std::cout << "Slot " << i
                      << ": addr=" << slot.tag
                      << " data=" << (int)slot.data
                      << std::endl;
            // shows which address is cached and what value it holds
        } else {
            std::cout << "Slot " << i << ": empty" << std::endl;
        }
    }
}
