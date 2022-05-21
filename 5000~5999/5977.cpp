#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    long long N, K;
    std::cin >> N >> K;

    std::vector<long long> E(N);
    for (long long& i : E) std::cin >> i;

    std::vector<long long> psum(N);
    psum[0] = E[0];
    for (int i = 1; i < N; ++i) psum[i] = psum[i - 1] + E[i];

    std::vector<long long> dp(N);
    std::deque<int> dq;

    dp[0] = psum[0];
    dq.push_back(0);

    auto C = [&](int i) { return i ? dp[i - 1] - psum[i] : -psum[i]; };
    for (int i = 1; i < N; ++i) {
        while (!dq.empty() && dq.front() < i - K) dq.pop_front();
        while (!dq.empty() && C(dq.back()) <= C(i)) dq.pop_back();
        dq.push_back(i);
        if (i < K)
            dp[i] = psum[i];
        else
            dp[i] = psum[i] + C(dq.front());
    }

    std::cout << dp.back() << '\n';

    return 0;
}