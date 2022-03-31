#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int w, n;
    std::cin >> w >> n;

    std::vector<int> A(n);
    for (int& i : A) std::cin >> i;

    std::sort(A.begin(), A.end());

    std::vector<bool> dp(w + 1);
    bool found = false;
    for (int i = 0; i < n - 2 && !found; ++i) {
        for (int j = 0; j < i && !found; ++j)
            if (A[i] + A[j] <= w) dp[A[i] + A[j]] = true;

        for (int j = i + 2; j < n && !found; ++j) {
            int k = w - A[i + 1] - A[j];
            if (0 <= k && k <= w && dp[k]) {
                std::cout << "YES\n";
                found = true;
            }
        }
    }

    if (!found) std::cout << "NO\n";

    return 0;
}
