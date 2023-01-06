#include <algorithm>
#include <deque>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using Fertility = std::vector<std::vector<int>>;
using Population = std::vector<std::vector<std::deque<int>>>;

class Simulation {
   private:
    const int N, K;
    Fertility fertility;
    Fertility growth;
    Population trees;

    void cycle() {
        // Spring and Summer
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) {
                auto required =
                    std::accumulate(trees[i][j].begin(), trees[i][j].end(), 0);
                int dead = 0;
                while (required > fertility[i][j]) {
                    dead += trees[i][j].back() / 2;
                    required -= trees[i][j].back();
                    trees[i][j].pop_back();
                }
                fertility[i][j] = fertility[i][j] - required + dead;

                for (auto& tree : trees[i][j]) ++tree;
            }

        // Fall
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                for (const auto& tree : trees[i][j])
                    if (tree % 5 == 0)
                        for (int k = 0; k < 8; ++k) {
                            int nx = i + dx[k];
                            int ny = j + dy[k];
                            if (0 <= nx && nx < N && 0 <= ny && ny < N)
                                trees[nx][ny].push_front(1);
                        }

        // Winter
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) fertility[i][j] += growth[i][j];
    }

    std::size_t count() const {
        std::size_t ans = 0;
        for (const auto& row : trees)
            for (const auto& cell : row) ans += cell.size();
        return ans;
    }

   public:
    Simulation(int N, int K, Fertility growth, Population trees)
        : N(N),
          K(K),
          fertility(N, std::vector<int>(N, 5)),
          growth(growth),
          trees(trees) {
        std::for_each(trees.begin(), trees.end(), [](auto& row) {
            std::for_each(row.begin(), row.end(), [](auto& cell) {
                std::sort(cell.begin(), cell.end());
            });
        });
    }

    int run() {
        for (int i = 0; i < K; ++i) cycle();
        return count();
    }
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M, K;
    std::cin >> N >> M >> K;

    Fertility growth(N, std::vector<int>(N));
    for (auto& row : growth)
        for (auto& cell : row) std::cin >> cell;

    Population trees(N, std::vector<std::deque<int>>(N));
    for (int i = 0; i < M; ++i) {
        int x, y, z;
        std::cin >> x >> y >> z;
        trees[x - 1][y - 1].push_back(z);
    }

    Simulation sim(N, K, growth, trees);
    std::cout << sim.run() << '\n';

    return 0;
}
