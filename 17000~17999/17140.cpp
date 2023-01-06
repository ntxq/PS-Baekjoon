#include <algorithm>
#include <deque>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

class Simulation {
   private:
    Matrix mat;
    unsigned r, c;
    int k;

    std::vector<int> sort(const std::vector<int>& row) {
        std::vector<std::pair<int, int>> counts;
        for (int i = 1; i < 101; ++i) counts.push_back({i, 0});

        for (const int& i : row)
            if (i) ++counts[i - 1].second;
        std::sort(counts.begin(), counts.end(),
                  [](const auto& a, const auto& b) {
                      return (a.second == b.second) ? a.first < b.first
                                                    : a.second < b.second;
                  });

        std::vector<int> result;
        for (const auto& [num, count] : counts)
            if (count) {
                result.push_back(num);
                result.push_back(count);
            }

        return result;
    }

    void equalize(Matrix& mat) {
        for (auto& row : mat)
            while (row.size() > 100) row.pop_back();

        std::size_t maxLen = 0;
        for (const auto& row : mat)
            if (row.size() > maxLen) maxLen = row.size();

        for (auto& row : mat)
            while (row.size() < maxLen) row.push_back(0);
    }

    void rowOp() {
        for (auto& row : mat) row = sort(row);
        equalize(mat);
    }

    void colOp() {
        Matrix t(mat[0].size(), std::vector<int>(mat.size()));
        for (std::size_t i = 0; i < mat.size(); ++i)
            for (std::size_t j = 0; j < mat[i].size(); ++j) t[j][i] = mat[i][j];

        for (auto& row : t) row = sort(row);
        equalize(t);

        mat = Matrix(t[0].size(), std::vector<int>(t.size()));
        for (std::size_t i = 0; i < t.size(); ++i)
            for (std::size_t j = 0; j < t[i].size(); ++j) mat[j][i] = t[i][j];
    }

   public:
    Simulation(unsigned r, unsigned c, int k, Matrix mat)
        : mat(mat), r(r), c(c), k(k) {}

    int run() {
        int time = 0;
        while (time < 101 && (r > mat.size() || c > mat[0].size() ||
                              mat[r - 1][c - 1] != k)) {
            if (mat.size() >= mat[0].size())
                rowOp();
            else
                colOp();
            ++time;
        }

        return (time < 101) ? time : -1;
    }
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned r, c;
    int k;
    std::cin >> r >> c >> k;

    std::vector<std::vector<int>> A(3, std::vector<int>(3));
    for (auto& row : A)
        for (auto& i : row) std::cin >> i;

    Simulation sim(r, c, k, A);
    std::cout << sim.run() << '\n';

    return 0;
}
