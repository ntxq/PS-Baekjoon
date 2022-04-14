#include <algorithm>
#include <iostream>
#include <vector>

void backtrack(std::vector<unsigned>& seq, std::vector<bool>& candidates,
               unsigned M) {
    if (seq.size() == M) {
        for (unsigned i : seq) std::cout << i << ' ';
        std::cout << '\n';
        return;
    }

    for (unsigned i = 1; i < candidates.size(); ++i)
        if (candidates[i]) {
            seq.push_back(i);
            candidates[i] = false;
            backtrack(seq, candidates, M);
            seq.pop_back();
            candidates[i] = true;
        }

    return;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned N, M;
    std::cin >> N >> M;

    std::vector<unsigned> seq;
    std::vector<bool> candidates(N + 1, true);
    backtrack(seq, candidates, M);

    return 0;
}
