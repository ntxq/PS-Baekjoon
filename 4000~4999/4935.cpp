#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int backtrack(int i, int lastSum, const std::string& s) {
    if (i == s.size()) return 1;

    int curSum = 0;
    int cnt = 0;

    for (int j = i; j < s.size(); ++j) {
        curSum += s[j] - '0';
        if (curSum >= lastSum) cnt += backtrack(j + 1, curSum, s);
    }

    return cnt;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int t = 0;
    std::string s;

    while (std::cin >> s && s != "bye") {
        std::cout << ++t << ". " << backtrack(0, 0, s) << '\n';
    }

    return 0;
}
