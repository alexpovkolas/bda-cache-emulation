//
// Created by Aliaksandr Paukalas on 10/14/18.
//

#include "Cache.h"

Cache::Cache(int cache_size, int associativity, int line_size):
    cache_size(cache_size), associativity(associativity),
    line_size(line_size), bank_lines_count(cache_size / line_size / associativity),
    lines(cache_size/line_size, -1), time(cache_size/line_size) {}

bool Cache::get_addr(int addr) {
    int cache_line = addr / line_size;
    int group = cache_line % bank_lines_count;
    std::time_t now = std::time(0);
    std::time_t oldest_line_time = now;
    int oldest_line_index = 0;
    for (int i = 0; i < associativity; ++i) {
        int index = bank_lines_count * i + group;
        int cached_line = lines[index];
        if (cached_line == cache_line) {
            time[index] = now;
            return true;
        }
        if (time[index] < oldest_line_time) {
            oldest_line_time = time[index];
            oldest_line_index = index;
        }
    }

    lines[oldest_line_index] = cache_line;
    time[oldest_line_index] = now;
    return false;
}