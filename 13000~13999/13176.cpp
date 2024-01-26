#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int solve(int curSize, int gNum) {
    static std::vector<std::vector<int>> memo(252, std::vector<int>(252, -1));
    
    if (curSize == 0) return gNum == 0;

    int& ret = memo[curSize][gNum];
    if (ret != -1) return ret;

    ret = 0;
    for (int i = 0; i < curSize; ++i)
        ret = (ret + solve(curSize - i - 1, gNum ^ i)) % 1000000007;
    return ret;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;
    std::cout << solve(n + 1, 0) << '\n';

    return 0;
}
