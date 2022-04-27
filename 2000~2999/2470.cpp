#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> A(N);
    for (int& i : A) std::cin >> i;

    std::sort(A.begin(), A.end());

    auto low = A.begin();
    auto high = A.end() - 1;

    int min = std::abs(A.front() + A.back());
    int candidates[2] = {A.front(), A.back()};

    while (low < high) {
        int diff = *low + *high;
        if (std::abs(diff) < min) {
            min = std::abs(diff);
            candidates[0] = *low;
            candidates[1] = *high;
        }

        if (diff < 0) {
            ++low;
        } else {
            --high;
        }
    }

    std::cout << candidates[0] << ' ' << candidates[1] << '\n';

    return 0;
}