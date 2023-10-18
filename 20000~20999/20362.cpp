#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::string S;

    std::cin >> N >> S;

    std::vector<std::string> names(N);
    std::vector<std::string> answers(N);

    int idx;
    std::string target;
    for (int i = 0; i < N; ++i) {
        std::cin >> names[i] >> answers[i];

        if (names[i] == S) {
            idx = i;
            target = answers[i];
        }
    }

    int cnt = 0;
    for (int i = 0; i < idx; ++i)
        if (answers[i] == target) ++cnt;

    std::cout << cnt << '\n';

    return 0;
}
