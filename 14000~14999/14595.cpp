#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<int> rooms(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        std::cin >> u >> v;
        ++rooms[u - 1];
        --rooms[v - 1];
    }

    std::partial_sum(rooms.begin(), rooms.end(), rooms.begin());

    int count = 0;
    for (int i = 0; i < N; ++i)
        if (rooms[i] == 0) ++count;

    std::cout << count << '\n';

    return 0;
}
