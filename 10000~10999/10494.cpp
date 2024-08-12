#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <set>
#include <vector>

bool is_consistent(int mark, int wheel, int M, const std::vector<int>& road) {
    for (int i = mark; i < M; i += wheel)
        if (road[i] == 0) return false;

    for (int i = mark; i >= 0; i -= wheel)
        if (road[i] == 0) return false;

    return true;
}

int backtrack(int i, int M, int N, std::vector<int>& road,
              const std::vector<int>& marks) {
    if (i == N) return 0;
    if (road[marks[i]] != 1) return backtrack(i + 1, M, N, road, marks);

    std::vector<int> candidates;
    for (int j = i + 1; j < N; ++j) {
        int wheel = std::abs(marks[i] - marks[j]);
        if (is_consistent(marks[i], wheel, M, road))
            candidates.push_back(wheel);
    }

    int min_wheels = backtrack(i + 1, M, N, road, marks) + 1;

    for (const int& wheel : candidates) {
        for (int j = marks[i]; j < M; j += wheel)
            if (road[j]) ++road[j];
        for (int j = marks[i]; j >= 0; j -= wheel)
            if (road[j]) ++road[j];

        min_wheels =
            std::min(min_wheels, backtrack(i + 1, M, N, road, marks) + 1);

        for (int j = marks[i]; j < M; j += wheel)
            if (road[j]) --road[j];
        for (int j = marks[i]; j >= 0; j -= wheel)
            if (road[j]) --road[j];
    }

    return min_wheels;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int M, N;
    while (std::cin >> M >> N) {
        std::vector<int> marks(N);
        std::vector<int> road(M);

        for (int& mark : marks) {
            std::cin >> mark;
            road[mark] = 1;
        }

        std::cout << backtrack(0, M, N, road, marks) << '\n';
    }

    return 0;
}
