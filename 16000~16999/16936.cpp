#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

int findPow(unsigned long long x) {
    int cnt = 0;
    while (x % 3 == 0) {
        x /= 3;
        ++cnt;
    }
    return cnt;
}

void backtrack(unsigned long long u, std::set<unsigned long long>& s,
               std::vector<unsigned long long>& order) {
    if (s.empty()) return;

    if (auto v = u / 3; u % 3 == 0 && s.contains(v)) {
        s.erase(v);
        order.push_back(v);
        return backtrack(v, s, order);
    }

    auto v = u * 2;
    s.erase(v);
    order.push_back(v);
    return backtrack(v, s, order);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    int maxPow = 0;
    unsigned long long start = -1;

    std::set<unsigned long long> s;
    for (int i = 0; i < N; ++i) {
        unsigned long long x;
        std::cin >> x;
        s.insert(x);

        int pow = findPow(x);
        if (pow > maxPow) {
            maxPow = pow;
            start = x;
        } else if (pow == maxPow && x < start) {
            start = x;
        }
    }

    std::vector<unsigned long long> order{start};
    s.erase(start);

    backtrack(start, s, order);
    for (const auto& x : order) std::cout << x << ' ';
    std::cout << '\n';

    return 0;
}