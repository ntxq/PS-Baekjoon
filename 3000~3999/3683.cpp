#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

bool try_kuhn(int u, std::vector<bool>& used, std::vector<int>& matched,
              const std::vector<std::vector<int>>& adj) {
    if (used[u]) return false;
    used[u] = true;

    for (int v : adj[u])
        if (matched[v] == -1 || try_kuhn(matched[v], used, matched, adj)) {
            matched[v] = u;
            return true;
        }

    return false;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int C, D, V;
        std::cin >> C >> D >> V;

        std::vector<std::vector<std::pair<int, int>>> cats(C);
        std::vector<std::vector<std::pair<int, int>>> dogs(D);
        for (int i = 0; i < V; ++i) {
            char pet_like, pet_dislike;
            int num_like, num_dislike;

            std::cin >> pet_like >> num_like >> pet_dislike >> num_dislike;
            if (pet_like == 'C')
                cats[num_like - 1].push_back({i, num_dislike - 1});
            else
                dogs[num_like - 1].push_back({i, num_dislike - 1});
        }

        std::vector<std::vector<int>> adj(V);

        for (const auto& cat : cats)
            for (const auto& [u, dislike] : cat)
                for (const auto& [v, _] : dogs[dislike]) {
                    adj[u].push_back(v);
                    adj[v].push_back(u);
                }

        for (const auto& dog : dogs)
            for (const auto& [u, dislike] : dog)
                for (const auto& [v, _] : cats[dislike]) {
                    adj[u].push_back(v);
                    adj[v].push_back(u);
                }

        std::vector<int> matched(V, -1);
        std::vector<bool> used(V);

        int cnt = 0;
        for (const auto& cat : cats)
            for (const auto& [u, _] : cat) {
                cnt += try_kuhn(u, used, matched, adj);
                std::fill(used.begin(), used.end(), false);
            }

        std::cout << V - cnt << '\n';
    }

    return 0;
}
