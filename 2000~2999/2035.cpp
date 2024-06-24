#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

long long backtrack(long long curNum, long long prev, std::string::iterator it,
                    const std::string::iterator& end) {
    if (it == end) {
        if (curNum > prev)
            return curNum;
        else
            return std::numeric_limits<long long>::max();
    }

    long long res = std::numeric_limits<long long>::max();

    long long num = curNum * 10 + (*it - '0');
    if (num < 0) return res;

    res = std::min(res, backtrack(num, prev, it + 1, end));
    if (num > prev) res = std::min(res, backtrack(0, num, it + 1, end));

    return res;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string s;
    std::cin >> s;

    std::cout << backtrack(0, -1, s.begin(), s.end()) << '\n';

    return 0;
}
