#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_set>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<bool> visited(20 * 50 + 1);

    int N;
    std::cin >> N;

    int count = 0;
    for (int i = 0; i <= N; ++i)
        for (int v = 0; v <= N - i; ++v)
            for (int x = 0; x <= N - i - v; ++x)
                if (int l = N - i - v - x;
                    !visited[i + v * 5 + x * 10 + l * 50]) {
                    visited[i + v * 5 + x * 10 + l * 50] = true;
                    ++count;
                }

    std::cout << count << '\n';

    return 0;
}