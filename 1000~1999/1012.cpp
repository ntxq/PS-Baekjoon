#include <iostream>
#include <utility>
#include <vector>

int countWorms(std::vector<std::vector<bool>>& field) {
    std::vector<std::pair<unsigned, unsigned>> s;

    int count = 0;
    for (unsigned i = 0; i < field.size(); ++i) {
        for (unsigned j = 0; j < field[i].size(); ++j) {
            if (!field[i][j]) {
                field[i][j] = true;
                s.push_back({i, j});
                ++count;
            }

            while (!s.empty()) {
                auto [x, y] = s.back();
                s.pop_back();

                if (x > 0 && !field[x - 1][y]) {
                    field[x - 1][y] = true;
                    s.push_back({x - 1, y});
                }

                if (x < field.size() - 1 && !field[x + 1][y]) {
                    field[x + 1][y] = true;
                    s.push_back({x + 1, y});
                }

                if (y > 0 && !field[x][y - 1]) {
                    field[x][y - 1] = true;
                    s.push_back({x, y - 1});
                }

                if (y < field[i].size() - 1 && !field[x][y + 1]) {
                    field[x][y + 1] = true;
                    s.push_back({x, y + 1});
                }
            }
        }
    }

    return count;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int cases;
    std::cin >> cases;

    for (int i = 0; i < cases; ++i) {
        int x, y, z;
        std::cin >> x >> y >> z;

        std::vector<std::vector<bool>> v(x, std::vector<bool>(y, true));
        for (int j = 0; j < z; ++j) {
            int a, b;
            std::cin >> a >> b;
            v[a][b] = false;
        }

        std::cout << countWorms(v) << '\n';
    }

    return 0;
}