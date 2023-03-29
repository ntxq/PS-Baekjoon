#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    long long n;
    std::cin >> n;

    std::cout << (n * n * n) << '\n' << 3 << '\n';

    return 0;
}
