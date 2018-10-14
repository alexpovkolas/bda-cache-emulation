//
// Created by Aliaksandr Paukalas on 10/14/18.
//

#ifndef CACHE_EMULATION_CACHE_H
#define CACHE_EMULATION_CACHE_H
#include <vector>
#include <ctime>

class Cache {
    int cache_size;
    int associativity;
    int line_size;
    int bank_lines_count;
    std::vector<std::time_t> time;
    std::vector<int> lines;
public:
    Cache(int cache_size, int associativity, int line_size);
    bool get_addr(int addr);
};


#endif //CACHE_EMULATION_CACHE_H
