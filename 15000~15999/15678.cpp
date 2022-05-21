#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, D;
    std::cin >> N >> D;

    std::vector<long long> K(N);
    for (auto& k : K) std::cin >> k;

    std::vector<long long> dp(N);
    std::deque<int> dq;

    long long max = K[0];
    dp[0] = K[0];
    dq.push_back(0);
    
    for (int i = 1; i < N; ++i) {
        while (!dq.empty() && dq.front() < i - D) dq.pop_front();
        dp[i] = std::max(dp[dq.front()], 0LL) + K[i];
        while (!dq.empty() && dp[dq.back()] < dp[i]) dq.pop_back();
        dq.push_back(i);

        if (dp[i] > max) max = dp[i];
    }

    std::cout << max << '\n';

    return 0;
}