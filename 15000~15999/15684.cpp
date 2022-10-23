#include <algorithm>
#include <iostream>
#include <vector>

int N, H;
std::vector<std::vector<bool>> ladders;

bool isValid() {
    for (int i = 0; i < N; ++i) {
        int x = i;
        for (int h = 0; h < H; ++h)
            if (ladders[h][x])
                ++x;
            else if (x > 0 && ladders[h][x - 1])
                --x;
        if (x != i) return false;
    }
    return true;
}

int dfs(int n, int h, int count, int limit) {
    if (count == limit || h == H) return isValid() ? count : 4;

    if (isValid()) return count;

    int ret = dfs((n + 1) % N, h + (n + 1) / N, count, limit);
    if (!ladders[h][n] && (n == 0 || !ladders[h][n - 1]) &&
        (n == N - 2 || !ladders[h][n + 1])) {
        ladders[h][n] = true;
        ret =
            std::min(ret, dfs((n + 1) % N, h + (n + 1) / N, count + 1, limit));
        ladders[h][n] = false;
    }

    return ret;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int M;
    std::cin >> N >> M >> H;

    ladders.assign(H, std::vector<bool>(N, false));
    for (int i = 0; i < M; ++i) {
        int a, b;
        std::cin >> a >> b;
        ladders[a - 1][b - 1] = true;
    }

    bool isSolved = false;
    for (int i = 0; i <= 3 && !isSolved; ++i) {
        int ret = dfs(0, 0, 0, i);
        if (ret != 4) {
            std::cout << ret << '\n';
            isSolved = true;
        }
    }

    if (!isSolved) std::cout << -1 << '\n';

    return 0;
}