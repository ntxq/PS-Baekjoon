#include <algorithm>
#include <iostream>
#include <string>

bool isPrime(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0) return false;

    return true;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int M, N;
    std::cin >> M >> N;

    int min = 0;
    int sum = 0;
    for (int i = M; i <= N; ++i)
        if (isPrime(i)) {
            sum += i;
            if (!min) min = i;
        }

    if (min)
        std::cout << sum << '\n' << min;
    else
        std::cout << -1;

    return 0;
}
