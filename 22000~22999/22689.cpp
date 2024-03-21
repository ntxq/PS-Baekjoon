#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

bool solve(std::string& str, const std::vector<int>& L) {
    for (int i = 1; i < L.size(); ++i) {
        int diff = L[i] - L[i - 1];

        if (std::abs(diff) > 1) return false;
        if (diff == 1 && str[i - 1] == '1') return false;
        if (diff == -1 && str[i - 1] == '0') return false;

        if (diff == 0) {
            str.push_back(str[i - 1]);
        } else if (diff == 1) {
            str.push_back('1');
        } else {
            str.push_back('0');
        }
    }

    return true;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    while (std::cin >> N >> M && N && M) {
        std::vector<int> L(N);
        for (int& l : L) std::cin >> l;

        std::string init;
        for (int i = 0; i < L[0]; ++i) init.push_back('1');
        for (int i = L[0]; i < M; ++i) init.push_back('0');

        bool is_possible = false;
        do {
            std::string str = init;
            is_possible = solve(str, L, M);
            if (is_possible) std::cout << str << '\n';
        } while (!is_possible &&
                 std::prev_permutation(init.begin(), init.end()));

        if (!is_possible) std::cout << "Goofy\n";
    }

    return 0;
}
