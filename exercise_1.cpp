#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;
using namespace chrono;

int sumArray(const int* data, int size) {
    int total = 0;
    for (int i = 0; i < size; ++i) total += data[i];
    return total;
}

int main() {
    srand(42);
    const vector<int> sizes{1000, 5000, 10000, 50000, 100000};

    cout << "n,avg_us\n";
    for (int size : sizes) {
        int* data = new int[size];
        for (int i = 0; i < size; ++i) data[i] = rand();

        long long elapsed = 0;
        volatile int result = 0;
        for (int run = 0; run < 5; ++run) {
            auto begin = high_resolution_clock::now();
            result = sumArray(data, size);
            auto end = high_resolution_clock::now();
            elapsed += duration_cast<microseconds>(end - begin).count();
        }

        cout << size << ',' << fixed << setprecision(2)
             << elapsed / 5.0 << '\n';
        delete[] data;
    }
    return 0;
}
