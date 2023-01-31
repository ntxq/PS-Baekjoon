#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> B(N);
    for (int& b : B) std::cin >> b;

    int count = 0;
    while (!std::all_of(B.begin(), B.end(), [](int b) { return b == 0; })) {
        auto it = std::find_if(B.begin(), B.end(), [](int b) { return b % 2; });
        if (it == B.end()) {
            std::transform(B.begin(), B.end(), B.begin(),
                           [](int b) { return b / 2; });
            ++count;
        } else {
            --*it;
            ++count;
        }
    }

    std::cout << count << '\n';

    return 0;
}
