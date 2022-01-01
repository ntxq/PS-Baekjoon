#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);

    int size;
    std::cin >> size;

    std::vector<int> arr;
    for (int i = 0; i < size; ++i) {
        int num;
        std::cin >> num;
        arr.push_back(num);
    }

    std::sort(arr.begin(), arr.end());

    std::cin >> size;
    for (int i = 0; i < size; ++i) {
        int num;
        std::cin >> num;
        std::cout << std::binary_search(arr.cbegin(), arr.cend(), num) << '\n';
    }

    return 0;
}