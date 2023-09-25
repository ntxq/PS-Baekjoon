#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    long double budget;
    std::cin >> budget;

    int days;
    std::cin >> days;

    long double best_profit = std::numeric_limits<long double>::lowest();
    long double min_price;
    std::cin >> min_price;

    for (int i = 1; i < days; ++i) {
        long double cur_price;
        std::cin >> cur_price;

        long double cur_profit = budget / min_price * cur_price - budget;
        best_profit = std::max(best_profit, cur_profit);
        min_price = std::min(min_price, cur_price);
    }

    std::cout << std::fixed << std::setprecision(2) << best_profit << '\n';

    return 0;
}
