#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;
using namespace chrono;

int findValue(const int* data, int size, int value) {
    for (int i = 0; i < size; ++i)
        if (data[i] == value) return i;
    return -1;
}

int main() {
    srand(43);
    const vector<int> sizes{1000, 5000, 10000, 50000, 100000};
    cout << "n,best_us,avg_us,worst_us\n";

    for (int size : sizes) {
        int* data = new int[size];
        for (int i = 0; i < size; ++i) data[i] = rand();

        long long bestTime = 0, averageTime = 0, worstTime = 0;
        volatile int answer = 0;

        for (int run = 0; run < 5; ++run) {
            auto start = high_resolution_clock::now();
            answer = findValue(data, size, data[0]);
            auto finish = high_resolution_clock::now();
            bestTime += duration_cast<microseconds>(finish - start).count();

            start = high_resolution_clock::now();
            answer = findValue(data, size, data[size / 2]);
            finish = high_resolution_clock::now();
            averageTime += duration_cast<microseconds>(finish - start).count();

            start = high_resolution_clock::now();
            answer = findValue(data, size, -999999);
            finish = high_resolution_clock::now();
            worstTime += duration_cast<microseconds>(finish - start).count();
        }

        cout << size << ',' << fixed << setprecision(2)
             << bestTime / 5.0 << ',' << averageTime / 5.0 << ','
             << worstTime / 5.0 << '\n';
        delete[] data;
    }
}
