#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using namespace chrono;

void bubbleSort(vector<int>& data) {
    for (int end = static_cast<int>(data.size()) - 1; end > 0; --end)
        for (int i = 0; i < end; ++i)
            if (data[i] > data[i + 1]) swap(data[i], data[i + 1]);
}

int main() {
    const vector<int> sizes{1000, 5000, 10000, 20000, 30000, 50000, 100000};
    mt19937 generator(47);
    cout << "n,bubble_ms,std_sort_ms,ratio\n";

    for (int n : sizes) {
        vector<int> source(n);
        for (int& x : source) x = static_cast<int>(generator());

        vector<int> first = source;
        auto start = high_resolution_clock::now();
        bubbleSort(first);
        auto finish = high_resolution_clock::now();
        double bubbleMs = duration<double, milli>(finish - start).count();

        vector<int> second = source;
        start = high_resolution_clock::now();
        sort(second.begin(), second.end());
        finish = high_resolution_clock::now();
        double standardMs = duration<double, milli>(finish - start).count();

        cout << n << ',' << fixed << setprecision(3)
             << bubbleMs << ',' << standardMs << ','
             << bubbleMs / standardMs << '\n';
    }
}
