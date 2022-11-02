#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, X;
    std::cin >> N >> X;

    std::vector<int> T(N);
    for (auto& t : T) std::cin >> t;

    int loser = -1;
    for (int i = 0; loser == -1; i = (i + 1) % N)
        if (T[i] < X)
            loser = i;
        else
            ++X;

    std::cout << loser + 1 << '\n';

    return 0;
}