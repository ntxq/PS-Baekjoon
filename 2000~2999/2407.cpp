#include <deque>
#include <iostream>
#include <map>

std::deque<int>& sanitize(std::deque<int>& v) {
    for (unsigned i = v.size() - 1; i > 0; --i)
        if (v[i] > 9) {
            v[i - 1] += v[i] / 10;
            v[i] %= 10;
        }

    if (v[0] > 9) {
        v.insert(v.begin(), v[0] / 10);
        v[1] %= 10;
    }

    return v;
}

std::deque<int> operator+(const std::deque<int>& lhs,
                          const std::deque<int>& rhs) {
    std::deque<int> result;

    auto i = lhs.rbegin(), j = rhs.rbegin();
    while (i != lhs.rend() && j != rhs.rend()) {
        result.push_front(*i + *j);
        ++i;
        ++j;
    }

    while (i != lhs.rend()) {
        result.push_front(*i);
        ++i;
    }

    while (j != rhs.rend()) {
        result.push_front(*j);
        ++j;
    }

    return sanitize(result);
}

std::deque<int> combination(int n, int m) {
    static std::map<std::pair<int, int>, std::deque<int>> dp;

    if (dp[{n, m}].size() > 0) return dp[{n, m}];

    if (m == 0 || m == n) {
        return dp[{n, m}] = {1};
    }

    if (m < n - m) return combination(n, n - m);

    return dp[{n, m}] = combination(n - 1, m - 1) + combination(n - 1, m);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::deque<int> result = combination(n, m);
    for (const int& i : result) std::cout << i;

    return 0;
}