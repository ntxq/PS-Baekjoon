#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string dna;
    std::cin >> dna;

    std::vector<std::vector<int>> dp(dna.size(),
                                     std::vector<int>(dna.size(), 0));

    for (int curSize = 1; curSize < dna.size(); ++curSize)
        for (int curStart = 0; curStart + curSize < dna.size(); ++curStart) {
            int curEnd = curStart + curSize;
            if ((dna[curStart] == 'a' && dna[curEnd] == 't') ||
                (dna[curStart] == 'g' && dna[curEnd] == 'c'))
                dp[curStart][curEnd] = dp[curStart + 1][curEnd - 1] + 2;

            for (int curMid = curStart; curMid < curEnd; ++curMid)
                dp[curStart][curEnd] =
                    std::max(dp[curStart][curEnd],
                             dp[curStart][curMid] + dp[curMid + 1][curEnd]);
        }

    std::cout << dp[0][dna.size() - 1] << '\n';

    return 0;
}
