#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>

int getMod(const std::string& s, int mod) {
    int remainder = 0;
    for (char c : s) remainder = (remainder * 10 + c - '0') % mod;
    return remainder;
}

void findProb(std::vector<std::vector<long long>>& dp,
              const std::vector<std::string>& S, int POW[], int STR[], int N,
              int K) {
    for (int state = 0; state < (1 << N); ++state)
        for (int i = 0; i < N; ++i)
            if ((state & (1 << i)) == 0) {
                int nextState = state | (1 << i);
                for (int j = 0; j < K; ++j) {
                    int nextK = ((j * POW[S[i].size()]) % K + STR[i]) % K;
                    dp[nextState][nextK] += dp[state][j];
                }
            }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::string> S(N);
    for (auto& s : S) std::cin >> s;

    int K;
    std::cin >> K;

    int POW[51];
    POW[0] = 1;
    for (int i = 1; i < 51; ++i) POW[i] = (POW[i - 1] * 10) % K;

    int STR[51];
    for (int i = 0; i < N; ++i) STR[i] = getMod(S[i], K);

    std::vector<std::vector<long long>> dp(1 << N,
                                           std::vector<long long>(K, 0));
    dp[0][0] = 1;

    findProb(dp, S, POW, STR, N, K);

    long long numer = dp[(1 << N) - 1][0];
    long long denom = 1;
    for (int i = 1; i <= N; ++i) denom *= i;

    long long gcd = std::gcd(numer, denom);
    std::cout << numer / gcd << '/' << denom / gcd << '\n';

    return 0;
}