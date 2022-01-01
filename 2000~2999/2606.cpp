#include <algorithm>
#include <iostream>
#include <vector>

std::vector<bool> dfs(int start,
                      const std::vector<std::vector<bool>>& network) {
    std::vector<bool> infected(network.size(), false);

    std::vector<int> s;
    s.push_back(start);
    infected[start] = true;

    while (!s.empty()) {
        int current = s.back();
        s.pop_back();

        for (unsigned i = 0; i < network[current].size(); ++i) {
            if (network[current][i] && !infected[i]) {
                infected[i] = true;
                s.push_back(i);
            }
        }
    }

    return infected;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int computers, connections;
    std::cin >> computers >> connections;

    std::vector<std::vector<bool>> network(computers,
                                           std::vector<bool>(computers, 0));
    for (int i = 0; i < connections; ++i) {
        int x, y;
        std::cin >> x >> y;

        network[x - 1][y - 1] = true;
        network[y - 1][x - 1] = true;
    }

    std::vector<bool> infected = dfs(0, network);
    std::cout << std::count(infected.cbegin(), infected.cend(), true) - 1;

    return 0;
}