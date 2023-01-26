#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

struct Egg {
    int durability, weight;
};

int backtrack(int idx, int acc, std::vector<Egg>& eggs, const int N) {
    if (idx == N) return acc;

    if (eggs[idx].durability <= 0) return backtrack(idx + 1, acc, eggs, N);

    int maxCracked = acc;

    for (int i = 0; i < N; ++i) {
        if (i == idx || eggs[i].durability <= 0) continue;

        eggs[idx].durability -= eggs[i].weight;
        eggs[i].durability -= eggs[idx].weight;

        int curCracked =
            (eggs[idx].durability <= 0) + (eggs[i].durability <= 0);
        maxCracked =
            std::max(maxCracked, backtrack(idx + 1, acc + curCracked, eggs, N));

        eggs[idx].durability += eggs[i].weight;
        eggs[i].durability += eggs[idx].weight;
    }

    return maxCracked;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<Egg> eggs(N);
    for (auto& egg : eggs) std::cin >> egg.durability >> egg.weight;

    std::cout << backtrack(0, 0, eggs, N) << '\n';

    return 0;
}