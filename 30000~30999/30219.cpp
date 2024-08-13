#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

double backtrack(int i, int N, std::vector<bool>& used,
                 std::vector<std::vector<std::pair<int, int>>>& triangles,
                 const std::vector<std::pair<int, int>>& points) {
    if (i == 3 * N) {
        double min_area = std::numeric_limits<double>::max();
        double max_area = 0;

        for (int i = 0; i < N; ++i) {
            double area = 0;
            for (int j = 0; j < 3; ++j)
                area +=
                    triangles[i][j].first * (triangles[i][(j + 1) % 3].second -
                                             triangles[i][(j + 2) % 3].second);
            area = std::abs(area) / 2;

            min_area = std::min(min_area, area);
            max_area = std::max(max_area, area);
        }

        return max_area - min_area;
    }

    if (used[i]) return backtrack(i + 1, N, used, triangles, points);

    double min_diff = std::numeric_limits<double>::max();
    for (int j = i + 1; j < 3 * N; ++j)
        if (!used[j])
            for (int k = j + 1; k < 3 * N; ++k)
                if (!used[k]) {
                    used[i] = used[j] = used[k] = true;
                    triangles.push_back({points[i], points[j], points[k]});
                    min_diff = std::min(
                        min_diff, backtrack(i + 1, N, used, triangles, points));
                    triangles.pop_back();
                    used[i] = used[j] = used[k] = false;
                }

    return min_diff;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::pair<int, int>> points(3 * N);
    for (int i = 0; i < 3 * N; ++i)
        std::cin >> points[i].first >> points[i].second;

    std::vector<bool> used(3 * N);
    std::vector<std::vector<std::pair<int, int>>> triangles;
    double min_diff = backtrack(0, N, used, triangles, points);

    std::cout << std::setprecision(1) << std::fixed << min_diff << '\n';

    return 0;
}
