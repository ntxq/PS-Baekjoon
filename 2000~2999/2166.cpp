#include <iomanip>
#include <iostream>
#include <utility>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::pair<long double, long double> p;
    std::cin >> p.first >> p.second;

    long long sum = 0;
    std::pair<long double, long double> pf = p;
    for (int i = 1; i < n; ++i) {
        std::pair<long double, long double> q;
        std::cin >> q.first >> q.second;

        sum += p.first * q.second - p.second * q.first;
        p = q;
    }

    sum += p.first * pf.second - p.second * pf.first;

    if (sum < 0) sum = -sum;

    std::cout << std::setprecision(1) << std::fixed << (sum / 2.0l);

    return 0;
}