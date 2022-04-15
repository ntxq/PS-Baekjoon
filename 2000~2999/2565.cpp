#include <algorithm>
#include <iostream>

int LIS(const std::vector<std::pair<int, int>>& wires) {
    std::vector<int> dp;
    for (auto [a, b] : wires) {
        auto it = std::lower_bound(dp.begin(), dp.end(), b);

        if (it == dp.end())
            dp.push_back(b);
        else
            *it = b;
    }

    return dp.size();
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::pair<int, int>> wires(N + 1);
    for (int i = 0; i < N; ++i) {
        int a, b;
        std::cin >> a >> b;

        wires[i] = {a, b};        
    }

    std::sort(wires.begin(), wires.end());

    std::cout << N - LIS(wires) + 1 << '\n';

    return 0;
}
