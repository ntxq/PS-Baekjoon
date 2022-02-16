#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

int travelSalesman(int src, int ret, std::bitset<16>& toVisit,
                   const std::vector<std::vector<int>>& weights) {
    static std::vector<std::vector<int>> dp(16, std::vector<int>(1 << 16));

    if (toVisit.none()) return weights[src][ret];
    if (dp[src][toVisit.to_ulong()]) return dp[src][toVisit.to_ulong()];

    int min = 0;
    for (int i = 0; i < 16; ++i) {
        if (toVisit[i] && weights[src][i]) {
            toVisit[i] = 0;
            int dist = travelSalesman(i, ret, toVisit, weights);
            if (int sumDist = dist + weights[src][i];
                dist && (sumDist < min || !min))
                min = sumDist;
            toVisit[i] = 1;
        }
    }

    return dp[src][toVisit.to_ulong()] = min;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<int>> weights(N, std::vector<int>(N));
    for (auto& row : weights)
        for (auto& weight : row) std::cin >> weight;

    std::bitset<16> toVisit;
    toVisit.set();

    toVisit[0] = 0;
    for (int i = N; i < 16; ++i) toVisit[i] = 0;

    std::cout << travelSalesman(0, 0, toVisit, weights) << '\n';

    return 0;
}