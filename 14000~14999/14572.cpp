#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, K, D;
    std::cin >> N >> K >> D;

    std::vector<int> skills(N);
    std::vector<std::vector<int>> known_algos(N);

    for (int i = 0; i < N; ++i) {
        int M;
        std::cin >> M >> skills[i];

        for (int j = 0; j < M; ++j) {
            int algo;
            std::cin >> algo;
            known_algos[i].push_back(algo);
        }
    }

    std::vector<int> students(N);
    std::iota(students.begin(), students.end(), 0);
    std::sort(students.begin(), students.end(),
              [&skills](int a, int b) { return skills[a] < skills[b]; });

    std::vector<int> group_algos(K + 1);
    for (int algo : known_algos[students[0]]) ++group_algos[algo];

    int l = 0, r = 1;
    long long max_score = 0LL;

    while (r < N) {
        if (skills[students[r]] - skills[students[l]] <= D) {
            for (int algo : known_algos[students[r]]) ++group_algos[algo];

            int group_size = r - l + 1;
            long long score = 0LL;
            for (int count : group_algos)
                if (0 < count && count < group_size) ++score;
            score *= group_size;

            max_score = std::max(max_score, score);
            ++r;
        } else {
            for (int algo : known_algos[students[l]]) --group_algos[algo];
            ++l;
        }
    }

    std::cout << max_score << '\n';

    return 0;
}
