#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    constexpr int ePeriod = 15;
    constexpr int sPeriod = 28;
    constexpr int mPeriod = 19;

    int E, S, M;
    std::cin >> E >> S >> M;
    --E, --S, --M;

    long long year = E;
    while (year % sPeriod != S) year += ePeriod;
    while (year % mPeriod != M) year += ePeriod * sPeriod;

    std::cout << year + 1 << '\n';

    return 0;
}