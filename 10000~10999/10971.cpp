#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int backtrack(std::vector<std::vector<int>>& dist, int size) {
    static std::vector<int> path{0};
    static std::vector<bool> visited(size, false);
    visited[0] = true;

    if (path.size() == static_cast<unsigned>(size)) {
        if (dist[path.back()][0] == 0) return std::numeric_limits<int>::max();

        int sum = 0;
        for (int i = 0; i < size; ++i)
            sum += dist[path[i]][path[(i + 1) % size]];
        return sum;
    }

    int min = std::numeric_limits<int>::max();
    for (int i = 0; i < size; ++i)
        if (!visited[i] && dist[path.back()][i] != 0) {
            visited[i] = true;
            path.push_back(i);
            min = std::min(min, backtrack(dist, size));
            path.pop_back();
            visited[i] = false;
        }

    return min;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<int>> dist(N, std::vector<int>(N));
    for (auto& row : dist)
        for (auto& elem : row) std::cin >> elem;

    std::cout << backtrack(dist, N) << '\n';

    return 0;
}