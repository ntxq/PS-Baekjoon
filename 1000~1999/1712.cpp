#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    long long A, B, C;
    std::cin >> A >> B >> C;

    long long profit = C - B;
    if (profit <= 0)
        std::cout << -1;
    else
        std::cout << A / profit + 1;

    return 0;
}
