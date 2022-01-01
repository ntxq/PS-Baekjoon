#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int size;
    std::cin >> size;

    std::allocator<int> alloc;
    int* arr = alloc.allocate(size);
    int* end = arr;
    for (int i = 0; i < size; ++i) {
        int x;
        std::cin >> x;
        alloc.construct(end++, x);
    }

    std::sort(arr, end);

    int cases;
    std::cin >> cases;
    for (int i = 0; i < cases; ++i) {
        int x;
        std::cin >> x;
        const auto& [first, last] = std::equal_range(arr, end, x);
        std::cout << (last - first) << ' ';
    }

    while (end != arr) alloc.destroy(--end);
    alloc.deallocate(arr, size);

    return 0;
}