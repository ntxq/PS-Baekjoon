#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

long long buyCombined(std::vector<int>& required, long long N, long long B,
                      long long C) {
    long long acc = 0;
    int prevSingle = 0;
    int prevDouble = 0;

    for (int i = 0; i < N; ++i) {
        int curDouble = std::min(prevSingle, required[i]);
        required[i] -= curDouble;
        acc += curDouble * C;

        int curTriple = std::min(prevDouble, required[i]);
        required[i] -= curTriple;
        acc += curTriple * C;

        int curSingle = required[i];
        acc += curSingle * B;

        prevSingle = curSingle;
        prevDouble = curDouble;
    }

    return acc;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    long long N, B, C;
    std::cin >> N >> B >> C;

    std::vector<int> required(N);
    for (int& i : required) std::cin >> i;

    if (B <= C)
        std::cout << std::accumulate(
                         required.begin(), required.end(), 0LL,
                         [&](long long a, int b) { return a + B * b; })
                  << '\n';
    else
        std::cout << buyCombined(required, N, B, C) << '\n';

    return 0;
}
