#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int fib[33];
    fib[0] = fib[1] = 1;
    for (int i = 2; i < 33; ++i) fib[i] = fib[i - 1] + fib[i - 2];

    int* grundyNums = new int[3000001];
    grundyNums[0] = 0;
    grundyNums[1] = 1;
    grundyNums[2] = 2;
    grundyNums[3] = 3;

    for (int i = 4; i < 3000001; ++i) {
        bool curNums[16]{};

        for (int j = 1; j < 33 && fib[j] <= i; ++j)
            curNums[grundyNums[i - fib[j]]] = true;

        for (int j = 0; j < 16; ++j)
            if (!curNums[j]) {
                grundyNums[i] = j;
                break;
            }
    }

    int N;
    std::cin >> N;

    int res = 0;
    for (int i = 0; i < N; ++i) {
        int x;
        std::cin >> x;
        res ^= grundyNums[x];
    }

    std::cout << (res ? "koosaga" : "cubelover") << '\n';

    return 0;
}
