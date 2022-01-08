#include <iostream>
#include <vector>

int timeConsume(int height, int block,
                const std::vector<std::vector<int>>& heights) {
    int time = 0;

    for (const auto& row : heights)
        for (const auto& box : row)
            if (box > height) {
                time += (box - height) * 2;
                block += box - height;
            } else {
                time += (height - box);
                block -= height - box;
            }

    return (block < 0 ? -1 : time);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m, b;
    std::cin >> n >> m >> b;

    std::vector<std::vector<int>> heights(n, std::vector<int>(m));
    for (auto& row : heights)
        for (auto& height : row) std::cin >> height;

    std::vector<int> times(257);
    for (int i = 0; i < 257 && times[i] != -1; ++i)
        times[i] = timeConsume(i, b, heights);

    int minTime = times[0];
    int minHeight = 1;

    for (int i = 0; i < 257 && times[i] != -1; ++i)
        if (times[i] <= minTime) {
            minTime = times[i];
            minHeight = i;
        }

    std::cout << minTime << ' ' << minHeight;

    return 0;
}