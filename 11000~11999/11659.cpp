#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> numbers(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        std::cin >> numbers[i];
        numbers[i] += numbers[i - 1];
    }

    for (int i = 0; i < m; ++i) {
        int from, to;
        std::cin >> from >> to;

        std::cout << numbers[to] - numbers[from - 1] << '\n';
    }

    return 0;
}