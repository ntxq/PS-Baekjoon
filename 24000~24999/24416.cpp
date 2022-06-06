#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    unsigned long long fibo[2]{0, 1};
    for (int i = 1; i < N; ++i) {
        unsigned long long next = fibo[0] + fibo[1];
        fibo[0] = fibo[1];
        fibo[1] = next;
    }

    std::cout << fibo[1] << ' ' << N - 2 << '\n';

    return 0;
}