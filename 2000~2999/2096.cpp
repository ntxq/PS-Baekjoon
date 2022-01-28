#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    int maxScore[2][3]{};
    int minScore[2][3]{};

    for (int i = 0; i < 3; ++i) {
        std::cin >> maxScore[0][i];
        minScore[0][i] = maxScore[0][i];
    }

    for (int i = 1; i < n; ++i) {
        const int cur = i % 2;
        const int alt = !cur;

        std::vector<int> scores(3);
        for (int i = 0; i < 3; ++i) std::cin >> scores[i];

        maxScore[cur][0] =
            std::max({maxScore[alt][0], maxScore[alt][1]}) + scores[0];
        maxScore[cur][1] =
            std::max({maxScore[alt][0], maxScore[alt][1], maxScore[alt][2]}) +
            scores[1];
        maxScore[cur][2] =
            std::max({maxScore[alt][1], maxScore[alt][2]}) + scores[2];

        minScore[cur][0] =
            std::min({minScore[alt][0], minScore[alt][1]}) + scores[0];
        minScore[cur][1] =
            std::min({minScore[alt][0], minScore[alt][1], minScore[alt][2]}) +
            scores[1];
        minScore[cur][2] =
            std::min({minScore[alt][1], minScore[alt][2]}) + scores[2];
    }

    const int last = (n - 1) % 2;
    std::cout
        << std::max({maxScore[last][0], maxScore[last][1], maxScore[last][2]})
        << ' '
        << std::min({minScore[last][0], minScore[last][1], minScore[last][2]});

    return 0;
}