#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int N, M;
        std::cin >> N >> M;

        std::vector<int> votes(N);

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                int vote;
                std::cin >> vote;

                votes[j] += vote;
            }
        }

        std::cout << std::max_element(votes.begin(), votes.end()) -
                         votes.begin() + 1
                  << '\n';
    }

    return 0;
}
