#include <iostream>
#import "Cache.h"
#include <iostream>


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