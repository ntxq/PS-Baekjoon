#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int getMaxArea(std::pair<int, int> first, std::pair<int, int> second, int H,
               int W) {
    auto [r1, c1] = first;
    auto [r2, c2] = second;
    int curArea = r1 * c1 + r2 * c2;

    if (c1 + c2 <= W && r1 <= H && r2 <= H) return curArea;
    if (r1 + r2 <= H && c1 <= W && c2 <= W) return curArea;

    // flip first
    std::swap(r1, c1);
    if (c1 + c2 <= W && r1 <= H && r2 <= H) return curArea;
    if (r1 + r2 <= H && c1 <= W && c2 <= W) return curArea;

    // flip both
    std::swap(r2, c2);
    if (c1 + c2 <= W && r1 <= H && r2 <= H) return curArea;
    if (r1 + r2 <= H && c1 <= W && c2 <= W) return curArea;

    // flip second
    std::swap(r1, c1);
    if (c1 + c2 <= W && r1 <= H && r2 <= H) return curArea;
    if (r1 + r2 <= H && c1 <= W && c2 <= W) return curArea;

    return 0;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int H, W, N;
    std::cin >> H >> W >> N;

    std::vector<std::pair<int, int>> stickers(N);
    for (auto& [r, c] : stickers) std::cin >> r >> c;

    int maxArea = 0;
    for (int i = 0; i < N - 1; ++i)
        for (int j = i + 1; j < N; ++j)
            if (auto curArea = getMaxArea(stickers[i], stickers[j], H, W);
                curArea > maxArea)
                maxArea = curArea;

    std::cout << maxArea << '\n';

    return 0;
}