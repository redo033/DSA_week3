#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;
using namespace chrono;

constexpr int MAX_SIZE = 100000;
int staticArray[MAX_SIZE];

int main() {
    srand(45);
    const vector<int> sizes{1000, 5000, 10000, 50000, 100000};
    cout << "n,static_us,dynamic_us,dynamic_bytes\n";

    for (int n : sizes) {
        int* dynamicArray = new int[n];
        long long staticTime = 0, dynamicTime = 0;
        volatile int guard = 0;

        for (int run = 0; run < 5; ++run) {
            auto start = high_resolution_clock::now();
            for (int i = 0; i < n; ++i) staticArray[i] = rand();
            auto finish = high_resolution_clock::now();
            staticTime += duration_cast<microseconds>(finish - start).count();

            start = high_resolution_clock::now();
            for (int i = 0; i < n; ++i) dynamicArray[i] = rand();
            finish = high_resolution_clock::now();
            dynamicTime += duration_cast<microseconds>(finish - start).count();
            guard += staticArray[n - 1] + dynamicArray[n - 1];
        }

        cout << n << ',' << fixed << setprecision(2)
             << staticTime / 5.0 << ',' << dynamicTime / 5.0 << ','
             << n * sizeof(int) << '\n';
        delete[] dynamicArray;
    }
}
