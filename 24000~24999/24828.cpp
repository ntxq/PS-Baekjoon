#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

bool backtrack(int a, int b, std::vector<int>& acc) {
    if (a == 0 && b == 0) return true;
    if (a == 0) return false;

    int cur_a = a % 10;
    int cur_b = b % 10;

    long long cur_pow = 0;
    long long cur_val = 1;

    while (cur_val <= b) {
        if (cur_val % 10 == cur_b) {
            acc.push_back(cur_pow);
            if (backtrack(a / 10, (b - cur_val) / 10, acc)) return true;
            acc.pop_back();
        }
        ++cur_pow;
        cur_val *= cur_a;
    }

    return false;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int a, b;
    std::cin >> a >> b;

    std::vector<int> acc;
    backtrack(a, b, acc);
    for (int i = acc.size() - 1; i >= 0; --i) std::cout << acc[i] << ' ';
    std::cout << '\n';

    return 0;
}
