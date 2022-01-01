#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int size;
    std::cin >> size;

    std::vector<int> arr;
    arr.reserve(size);

    for (int i = 0; i < size; ++i) {
        int number;
        std::cin >> number;
        arr.push_back(number);
    }

    std::sort(arr.begin(), arr.end());

    for (const int& i : arr) std::cout << i << '\n';

    return 0;
}