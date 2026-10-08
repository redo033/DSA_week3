#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;
using namespace chrono;

int sumArray(const int* a, int n) {
    int total = 0;
    for (int i = 0; i < n; ++i) total += a[i];
    return total;
}

void sortBubble(int* a, int n) {
    for (int last = n - 1; last > 0; --last) {
        for (int i = 0; i < last; ++i) {
            if (a[i] > a[i + 1]) swap(a[i], a[i + 1]);
        }
    }
}

int main() {
    srand(44);
    const vector<int> sizes{1000, 5000, 10000, 20000, 30000};
    cout << "n,sum_us,bubble_us\n";

    for (int n : sizes) {
        vector<int> original(n);
        for (int& value : original) value = rand();

        long long sumTime = 0, sortTime = 0;
        volatile int guard = 0;
        for (int run = 0; run < 3; ++run) {
            auto start = high_resolution_clock::now();
            guard = sumArray(original.data(), n);
            auto finish = high_resolution_clock::now();
            sumTime += duration_cast<microseconds>(finish - start).count();

            vector<int> copy(original);
            start = high_resolution_clock::now();
            sortBubble(copy.data(), n);
            finish = high_resolution_clock::now();
            sortTime += duration_cast<microseconds>(finish - start).count();
        }

        cout << n << ',' << fixed << setprecision(2)
             << sumTime / 3.0 << ',' << sortTime / 3.0 << '\n';
    }
}
