#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int size;
    std::cin >> size;

    int* coordinates = new int[size];
    int** sorted = new int*[size];

    for (int i = 0; i < size; ++i) {
        int x;
        std::cin >> x;
        coordinates[i] = x;
        sorted[i] = &coordinates[i];
    }

    std::sort(sorted, sorted + size, [](int* a, int* b) { return *a < *b; });

    for (int i = 0, prev = *sorted[0], count = 0; i < size; ++i) {
        if (*sorted[i] == prev)
            *sorted[i] = count;
        else {
            prev = *sorted[i];
            *sorted[i] = ++count;
        }
    }

    for (int i = 0; i < size; ++i) std::cout << coordinates[i] << ' ';

    delete[] coordinates;
    delete[] sorted;

    return 0;
}