#include <algorithm>
#include <iostream>
#include <vector>

constexpr unsigned int parent(unsigned int i) { return (i - 1) / 2; }
constexpr unsigned int left(unsigned int i) { return 2 * i + 1; }
constexpr unsigned int right(unsigned int i) { return 2 * i + 2; }

void maxHeapify(std::vector<int>& heap, unsigned int i) {
    unsigned int l = left(i);
    unsigned int r = right(i);

    unsigned largest = i;
    if (l < heap.size() && heap[l] > heap[i]) largest = l;

    if (r < heap.size() && heap[r] > heap[largest]) largest = r;

    if (largest != i) {
        std::swap(heap[i], heap[largest]);
        maxHeapify(heap, largest);
    }
}

int heapExtract(std::vector<int>& heap) {
    if (!heap.size()) return 0;

    int max = heap.front();
    heap.front() = heap.back();
    heap.pop_back();
    maxHeapify(heap, 0);

    return max;
}

void heapInsert(std::vector<int>& heap, int key) {
    heap.push_back(key);

    unsigned i = heap.size() - 1;
    while (i && heap[parent(i)] < heap[i]) {
        std::swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int cases;
    std::cin >> cases;

    std::vector<int> heap;
    for (int x; std::cin >> x;) {
        if (x)
            heapInsert(heap, x);
        else
            std::cout << heapExtract(heap) << '\n';
    }

    return 0;
}