#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using namespace chrono;

struct Node {
    int value;
    Node* next;
};

Node* makeList(const vector<int>& values) {
    Node* first = nullptr;
    Node* last = nullptr;

    for (int value : values) {
        Node* item = new Node{value, nullptr};
        if (first == nullptr) first = item;
        else last->next = item;
        last = item;
    }
    return first;
}

bool contains(Node* first, int target) {
    for (Node* current = first; current != nullptr; current = current->next)
        if (current->value == target) return true;
    return false;
}

void destroyList(Node* first) {
    while (first != nullptr) {
        Node* next = first->next;
        delete first;
        first = next;
    }
}

int main() {
    const vector<int> sizes{1000, 5000, 10000, 50000, 100000};
    mt19937 generator(49);
    cout << "n,structure,insert_us,search_us,bytes_per_element,total_bytes\n";

    for (int n : sizes) {
        vector<int> input(n);
        for (int& value : input) value = static_cast<int>(generator());
        int target = input[n - 2];

        vector<int> values;
        auto start = high_resolution_clock::now();
        for (int x : input) values.push_back(x);
        auto finish = high_resolution_clock::now();
        auto vectorInsert = duration_cast<microseconds>(finish - start).count();

        start = high_resolution_clock::now();
        volatile auto foundVector = find(values.begin(), values.end(), target);
        finish = high_resolution_clock::now();
        auto vectorSearch = duration_cast<microseconds>(finish - start).count();

        int* array = new int[n];
        start = high_resolution_clock::now();
        for (int i = 0; i < n; ++i) array[i] = input[i];
        finish = high_resolution_clock::now();
        auto arrayInsert = duration_cast<microseconds>(finish - start).count();

        start = high_resolution_clock::now();
        volatile int position = -1;
        for (int i = 0; i < n; ++i) {
            if (array[i] == target) { position = i; break; }
        }
        finish = high_resolution_clock::now();
        auto arraySearch = duration_cast<microseconds>(finish - start).count();

        start = high_resolution_clock::now();
        Node* head = makeList(input);
        finish = high_resolution_clock::now();
        auto listInsert = duration_cast<microseconds>(finish - start).count();

        start = high_resolution_clock::now();
        volatile bool foundList = contains(head, target);
        finish = high_resolution_clock::now();
        auto listSearch = duration_cast<microseconds>(finish - start).count();

        size_t vectorMemory = values.capacity() * sizeof(int);
        size_t arrayMemory = n * sizeof(int);
        size_t listMemory = n * sizeof(Node);

        cout << n << ",vector," << vectorInsert << ',' << vectorSearch << ','
             << sizeof(int) << ',' << vectorMemory << '\n';
        cout << n << ",array," << arrayInsert << ',' << arraySearch << ','
             << sizeof(int) << ',' << arrayMemory << '\n';
        cout << n << ",linked_list," << listInsert << ',' << listSearch << ','
             << sizeof(Node) << ',' << listMemory << '\n';

        delete[] array;
        destroyList(head);
    }
}
