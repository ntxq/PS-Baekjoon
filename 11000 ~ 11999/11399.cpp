#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int size;
    std::cin >> size;

    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) std::cin >> arr[i];

    std::sort(arr.begin(), arr.end());

    int sum = 0;
    for (int i = 0; i < size; ++i) sum += arr[i] * (size - i);

    std::cout << sum;

    return 0;
}