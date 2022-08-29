#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    const std::vector<int> required{1, 1, 2, 2, 2, 8};

    for (int i = 0; i < 6; ++i) {
        int n;
        std::cin >> n;
        std::cout << (required[i] - n) << ' ';
    }
    std::cout << '\n';

    return 0;
}