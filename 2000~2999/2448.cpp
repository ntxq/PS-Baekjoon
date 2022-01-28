#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void draw(int level, int x, int y, const std::vector<std::string>& base,
          std::vector<std::vector<char>>& map) {
    if (level == 1) {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 5; ++j) map[i + x][j + y] = base[i][j];

        return;
    }

    draw(level / 2, x, y + 3 * level / 2, base, map);
    draw(level / 2, x + 3 * level / 2, y, base, map);
    draw(level / 2, x + 3 * level / 2, y + 3 * level, base, map);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::string> base = {"  *  ", " * * ", "*****"};
    std::vector<std::vector<char>> map(n, std::vector<char>(2 * n - 1, ' '));

    draw(n / 3, 0, 0, base, map);
    for (const auto& i : map) {
        for (const auto& j : i) std::cout << j;
        std::cout << '\n';
    }

    return 0;
}