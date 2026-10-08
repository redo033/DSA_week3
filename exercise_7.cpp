#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using namespace chrono;

int main() {
    const vector<int> sizes{50, 100, 200, 400};
    mt19937 generator(48);
    cout << "n,multiply_ms,approx_bytes\n";

    for (int n : sizes) {
        vector<vector<int>> first(n, vector<int>(n));
        vector<vector<int>> second(n, vector<int>(n));
        vector<vector<int>> result(n, vector<int>(n, 0));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                first[i][j] = static_cast<int>(generator() % 100);
                second[i][j] = static_cast<int>(generator() % 100);
            }
        }

        auto start = high_resolution_clock::now();
        for (int i = 0; i < n; ++i)
            for (int k = 0; k < n; ++k)
                for (int j = 0; j < n; ++j)
                    result[i][j] += first[i][k] * second[k][j];
        auto finish = high_resolution_clock::now();

        double elapsed = duration<double, milli>(finish - start).count();
        unsigned long long memory = 3ULL * n * n * sizeof(int);
        cout << n << ',' << fixed << setprecision(3)
             << elapsed << ',' << memory << '\n';
    }
}
