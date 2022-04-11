#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    for (int i = 2; i <= N; ++i)
        while (N % i == 0) {
            N /= i;
            std::cout << i << '\n';
        }

    return 0;
}
