#include <chrono>
#include <iostream>
#include <vector>

using namespace std;
using namespace chrono;

long long fibonacciRecursive(int n) {
    if (n < 2) return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

long long fibonacciLoop(int n) {
    long long previous = 0, current = 1;
    for (int i = 0; i < n; ++i) {
        long long next = previous + current;
        previous = current;
        current = next;
    }
    return previous;
}

int main() {
    const vector<int> recursiveTests{20, 25, 30, 35};
    const vector<int> iterativeTests{1000, 100000, 1000000};

    cout << "recursive\n" << "n,time_us\n";
    for (int n : recursiveTests) {
        auto start = high_resolution_clock::now();
        volatile long long value = fibonacciRecursive(n);
        auto finish = high_resolution_clock::now();
        cout << n << ','
             << duration_cast<microseconds>(finish - start).count() << '\n';
    }

    cout << "iterative\n" << "n,time_us\n";
    for (int n : iterativeTests) {
        auto start = high_resolution_clock::now();
        volatile long long value = fibonacciLoop(n);
        auto finish = high_resolution_clock::now();
        cout << n << ','
             << duration_cast<microseconds>(finish - start).count() << '\n';
    }
}
