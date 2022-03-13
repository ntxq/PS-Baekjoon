#include <algorithm>
#include <iostream>
#include <numeric>
#include <optional>
#include <vector>

void toggle(int x, int y, std::vector<std::vector<bool>>& lights) {
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    lights[x][y] = !lights[x][y];
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (0 <= nx && nx < 10 && 0 <= ny && ny < 10)
            lights[nx][ny] = !lights[nx][ny];
    }
}

std::optional<int> solve(std::vector<std::vector<bool>>& lights) {
    int count = 0;
    for (int i = 1; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            if (lights[i - 1][j]) {
                toggle(i, j, lights);
                ++count;
            }

    return (std::any_of(lights.back().begin(), lights.back().end(),
                        [](bool b) { return b; }))
               ? std::nullopt
               : std::optional<int>(count);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<std::vector<bool>> lights(10, std::vector<bool>(10));
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            char c;
            std::cin >> c;
            lights[i][j] = c == 'O';
        }
    }

    int min_cnt = -1;
    for (int i = 0; i < (1 << 10); ++i) {
        auto lights_copy{lights};

        int init_cnt = 0;
        for (int j = 0; j < 10; ++j)
            if (i & (1 << j)) {
                toggle(0, j, lights_copy);
                ++init_cnt;
            }

        auto result = solve(lights_copy);

        if (result.has_value() &&
            (min_cnt == -1 || result.value() + init_cnt < min_cnt))
            min_cnt = result.value() + init_cnt;
    }

    std::cout << min_cnt << '\n';

    return 0;
}
