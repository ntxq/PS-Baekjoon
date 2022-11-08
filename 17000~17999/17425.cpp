#include <array>
#include <iostream>

constexpr int TABLE_SIZE = 1000001;

std::array<long long, TABLE_SIZE> Table = [] {
    std::array<long long, TABLE_SIZE> A = {};
    for (int i = 1; i < TABLE_SIZE; ++i)
        for (int j = 1; i * j < TABLE_SIZE; ++j) A[i * j] += i;
    for (int i = 1; i < TABLE_SIZE; ++i) A[i] += A[i - 1];
    return A;
}();

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int N;
        std::cin >> N;
        std::cout << Table[N] << '\n';
    }

    return 0;
}