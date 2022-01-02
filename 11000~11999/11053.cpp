#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int size;
    std::cin >> size;

    std::vector<int> arr(size);
    for (int& i : arr) std::cin >> i;

    std::vector<int> seq;
    for (const int& i : arr) {
        auto it = std::lower_bound(seq.begin(), seq.end(), i);
        if (it == seq.end())
            seq.push_back(i);
        else
            *it = i;
    }

    std::cout << seq.size();

    return 0;
}