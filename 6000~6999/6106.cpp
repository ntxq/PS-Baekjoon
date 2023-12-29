#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    int money = 0;
    int debt = 0;
    int debt_loc = std::numeric_limits<int>::max();
    int dist = 0;

    for (int i = 0; i < N; ++i) {
        int cow;
        std::cin >> cow;

        if (cow > 0) {
            money += cow;
        } else {
            debt -= cow;
            debt_loc = std::min(debt_loc, i);
        }

        if (debt > 0 && money >= debt) {
            dist += (i - debt_loc) * 2;
            money -= debt;
            debt = 0;
            debt_loc = std::numeric_limits<int>::max();
        }

        ++dist;
    }

    std::cout << dist << '\n';

    return 0;
}
