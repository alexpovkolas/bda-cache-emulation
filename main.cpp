#include <iostream>
#include <vector>
#include <iostream>

class Cache {
    int cache_size;
    int associativity;
    int line_size;
    int bank_lines_count;
    int tick;
    std::vector<int> time;
    std::vector<int> lines;
public:
    Cache(int cache_size, int associativity, int line_size);
    bool get_addr(int addr);
};

Cache::Cache(int cache_size, int associativity, int line_size):
        cache_size(cache_size), associativity(associativity),
        line_size(line_size), bank_lines_count(cache_size / line_size / associativity),
        lines(cache_size/line_size, -1), time(cache_size/line_size, 0), tick(0) {}


bool Cache::get_addr(int addr) {
    int line_number = addr / line_size;
    int bank_line_number = line_number % bank_lines_count;
    int oldest_line_time = tick + 1;
    int oldest_line_index = -1;
    for (int i = 0; i < associativity; ++i) {
        int index = bank_lines_count * i + bank_line_number;
        int cached_line_number = lines[index];
        if (cached_line_number == line_number) {
            time[index] = tick++;
            return true;
        }
        if (time[index] < oldest_line_time) {
            oldest_line_time = time[index];
            oldest_line_index = index;
        }
    }

    lines[oldest_line_index] = line_number;
    time[oldest_line_index] = tick++;
    return false;
}

using namespace std;

int main() {
    int cacheSize = 0;
    int associativity = 0;
    int lineSize = 0;
    int n = 0;

    cin >> cacheSize >> associativity >> lineSize >> n;
    vector<int> addresses(n);
    for (int i = 0; i < n; ++i) {
        cin >> addresses[i];
    }

    int misses_count = 0;
    int hit_count = 0;
    Cache cache(cacheSize, associativity, lineSize);
    for (int address : addresses) {
        cache.get_addr(address) ? hit_count++ : misses_count++;
    }

    cout << hit_count << " " << misses_count << std::endl;


    return 0;
}