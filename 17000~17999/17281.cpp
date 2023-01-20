#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

class Baseball {
   private:
    std::vector<std::vector<int>> performance;
    std::vector<bool> bases;
    const int maxInning;

    int score = 0;
    int outs = 0;
    int curInning = 0;
    int curPlayer = 0;

    void playBall(int player) {
        int result = performance[curInning][player];
        switch (result) {
            case 0:
                ++outs;
                break;

            case 1:
                if (bases[2]) ++score;
                bases[2] = bases[1];
                bases[1] = bases[0];
                bases[0] = true;
                break;

            case 2:
                if (bases[2]) ++score;
                if (bases[1]) ++score;
                bases[2] = bases[0];
                bases[1] = true;
                bases[0] = false;
                break;

            case 3:
                if (bases[2]) ++score;
                if (bases[1]) ++score;
                if (bases[0]) ++score;
                bases[2] = true;
                bases[1] = false;
                bases[0] = false;
                break;

            case 4:
                if (bases[2]) ++score;
                if (bases[1]) ++score;
                if (bases[0]) ++score;
                ++score;
                bases[2] = false;
                bases[1] = false;
                bases[0] = false;
                break;
        }

        return;
    }

    void playInning(const std::vector<int>& order) {
        outs = 0;
        bases = {false, false, false};

        while (outs < 3) {
            int player = order[curPlayer];
            playBall(player);
            curPlayer = (curPlayer + 1) % 9;
        }

        return;
    }

   public:
    Baseball(std::vector<std::vector<int>>& performance, int maxInning)
        : performance(performance), bases(3, false), maxInning(maxInning) {}

    int getScore(const std::vector<int>& order) {
        score = 0;
        curPlayer = 0;
        curInning = 0;

        while (curInning < maxInning) {
            playInning(order);
            ++curInning;
        }

        return score;
    }
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<int>> performance(N, std::vector<int>(9));
    for (auto& row : performance)
        for (auto& cell : row) std::cin >> cell;

    int maxScore = std::numeric_limits<int>::min();
    Baseball baseball(performance, N);
    std::vector<int> order{1, 2, 3, 4, 5, 6, 7, 8};

    do {
        std::vector<int> curOder(order);
        curOder.insert(curOder.begin() + 3, 0);
        maxScore = std::max(maxScore, baseball.getScore(curOder));
    } while (std::next_permutation(order.begin(), order.end()));

    std::cout << maxScore << '\n';

    return 0;
}