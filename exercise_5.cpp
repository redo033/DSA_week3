#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;
using namespace chrono;

int main() {
    srand(46);
    const vector<int> sizes{1000, 5000, 10000, 50000, 100000};
    cout << "n,push_back_us,reserve_push_back_us\n";

    for (int n : sizes) {
        long long normalTime = 0, reservedTime = 0;
        volatile int guard = 0;

        for (int run = 0; run < 5; ++run) {
            vector<int> normal;
            auto start = high_resolution_clock::now();
            for (int i = 0; i < n; ++i) normal.push_back(rand());
            auto finish = high_resolution_clock::now();
            normalTime += duration_cast<microseconds>(finish - start).count();
            guard += normal.back();

            vector<int> reserved;
            reserved.reserve(n);
            start = high_resolution_clock::now();
            for (int i = 0; i < n; ++i) reserved.push_back(rand());
            finish = high_resolution_clock::now();
            reservedTime += duration_cast<microseconds>(finish - start).count();
            guard += reserved.back();
        }

        cout << n << ',' << fixed << setprecision(2)
             << normalTime / 5.0 << ',' << reservedTime / 5.0 << '\n';
    }

    vector<int> values;
    cout << "capacity_jumps:";
    size_t oldCapacity = values.capacity();
    for (int i = 0; i < 100000; ++i) {
        values.push_back(i);
        if (values.capacity() != oldCapacity) {
            cout << ' ' << values.capacity();
            oldCapacity = values.capacity();
        }
    }
    cout << '\n';
}
