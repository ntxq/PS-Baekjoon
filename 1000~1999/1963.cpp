#include <array>
#include <iostream>
#include <queue>
#include <limits>
#include <vector>

constexpr int TABLE_SIZE = 10000;

constexpr std::array<bool, TABLE_SIZE> isPrime = [] {
    std::array<bool, TABLE_SIZE> A{};
    for (int i = 2; i < TABLE_SIZE; i++) A[i] = true;

    for (int i = 2; i * i < TABLE_SIZE; ++i)
        if (A[i])
            for (int j = i * i; j < TABLE_SIZE; j += i) A[j] = false;

    return A;
}();

int bfs(int s, int t) {
    std::queue<std::pair<int, int>> q;
    std::vector<bool> visited(TABLE_SIZE);

    q.push({s, 0});
    visited[s] = true;

    while (!q.empty()) {
        auto [u, d] = q.front();
        q.pop();

        if (u == t) return d;

        // change tousands
        for (int i = 1; i <= 9; i++) {
            int v = u + (i - u / 1000) * 1000;
            if (isPrime[v] && !visited[v]) {
                q.push({v, d + 1});
                visited[v] = true;
            }
        }

        // change hundreds
        for (int i = 0; i <= 9; i++) {
            int v = u + (i - u / 100 % 10) * 100;
            if (isPrime[v] && !visited[v]) {
                q.push({v, d + 1});
                visited[v] = true;
            }
        }

        // change tens
        for (int i = 0; i <= 9; i++) {
            int v = u + (i - u / 10 % 10) * 10;
            if (isPrime[v] && !visited[v]) {
                q.push({v, d + 1});
                visited[v] = true;
            }
        }

        // change ones
        for (int i = 0; i <= 9; i++) {
            int v = u + (i - u % 10);
            if (isPrime[v] && !visited[v]) {
                q.push({v, d + 1});
                visited[v] = true;
            }
        }
    }

    return -1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int s, t;
        std::cin >> s >> t;
        int dist = bfs(s, t);
        if (dist == -1)
            std::cout << "Impossible\n";
        else
            std::cout << dist << '\n';
    }

    return 0;
}
