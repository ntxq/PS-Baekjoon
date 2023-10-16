#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, Q;
    std::cin >> N >> Q;

    std::vector<int> notes(N);
    for (int& note : notes) std::cin >> note;

    for (int i = 1; i < N; ++i) notes[i] += notes[i - 1];

    for (int i = 0; i < Q; ++i) {
        int q;
        std::cin >> q;

        std::cout << std::upper_bound(notes.begin(), notes.end(), q) -
                         notes.begin() + 1
                  << '\n';
    }

    return 0;
}
