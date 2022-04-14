#include <algorithm>
#include <iostream>
#include <vector>

void backtrack(std::vector<unsigned>& seq, unsigned N, unsigned M) {
    if (seq.size() == M) {
        for (unsigned i : seq) std::cout << i << ' ';
        std::cout << '\n';
        return;
    }

    for (unsigned i = 1; i <= N; ++i) {
        seq.push_back(i);
        backtrack(seq, N, M);
        seq.pop_back();
    }

    return;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned N, M;
    std::cin >> N >> M;

    std::vector<unsigned> seq;
    backtrack(seq, N, M);

    return 0;
}
