#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

double findSum(const std::vector<bool>& visited,
               const std::vector<std::pair<int, int>>& points) {
    double x = 0;
    double y = 0;

    for (unsigned i = 0; i < points.size(); ++i)
        if (visited[i]) {
            x += points[i].first;
            y += points[i].second;
        } else {
            x -= points[i].first;
            y -= points[i].second;
        }

    return std::sqrt(x * x + y * y);
}

double dfs(int index, unsigned level, std::vector<bool>& visited,
           const std::vector<std::pair<int, int>>& points) {
    if (level == visited.size() / 2) return findSum(visited, points);

    double minSum = std::numeric_limits<double>::max();
    for (unsigned i = index; i < points.size(); ++i) {
        visited[i] = true;
        if (double curSum = dfs(i + 1, level + 1, visited, points);
            curSum < minSum)
            minSum = curSum;
        visited[i] = false;
    }

    return minSum;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        int n;
        std::cin >> n;

        std::vector<bool> visited(n);
        std::vector<std::pair<int, int>> points(n);
        for (auto& p : points) std::cin >> p.first >> p.second;

        std::cout << std::fixed << dfs(0, 0, visited, points) << '\n';
    }

    return 0;
}
