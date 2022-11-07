#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    long long sum = 0;
    for (int i = 1; i <= N; ++i) sum += N / i * i;

    std::cout << sum << '\n';

    return 0;
}