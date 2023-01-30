#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

int N;
std::vector<int> population;
std::vector<std::vector<int>> adj;

int minDiff = std::numeric_limits<int>::max();

bool isValidSplit(const std::vector<bool>& splits) {
    std::queue<int> q;
    std::vector<bool> visited(N);

    for (int i = 0; i < N; ++i)
        if (splits[i]) {
            q.push(i);
            visited[i] = true;
            break;
        }

    for (int i = 0; i < N; ++i)
        if (!splits[i]) {
            q.push(i);
            visited[i] = true;
            break;
        }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (visited[v]) continue;
            if (splits[u] != splits[v]) continue;

            visited[v] = true;
            q.push(v);
        }
    }

    return std::all_of(visited.begin(), visited.end(),
                       [](bool b) { return b; });
}

int countDiff(const std::vector<bool>& splits) {
    int sum1 = 0;
    int sum2 = 0;

    for (int i = 0; i < N; ++i)
        if (splits[i])
            sum1 += population[i];
        else
            sum2 += population[i];

    return std::abs(sum1 - sum2);
}

void backtrack(int idx, std::vector<bool>& splits) {
    if (idx == N) {
        if (isValidSplit(splits))
            minDiff = std::min(minDiff, countDiff(splits));
        return;
    }

    splits[idx] = true;
    backtrack(idx + 1, splits);
    splits[idx] = false;
    backtrack(idx + 1, splits);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::cin >> N;

    population.resize(N);
    for (int& i : population) std::cin >> i;

    adj.resize(N);
    for (int i = 0; i < N; ++i) {
        int M;
        std::cin >> M;

        for (int j = 0; j < M; ++j) {
            int v;
            std::cin >> v;
            adj[i].push_back(v - 1);
            adj[v - 1].push_back(i);
        }
    }

    std::vector<bool> splits(N);
    backtrack(0, splits);

    std::cout << (minDiff == std::numeric_limits<int>::max() ? -1 : minDiff)
              << '\n';

    return 0;
}
