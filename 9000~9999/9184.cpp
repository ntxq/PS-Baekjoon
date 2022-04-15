#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>

long long w(int a, int b, int c) {
    static std::optional<long long> dp[21][21][21];

    if (a <= 0 || b <= 0 || c <= 0) return 1;
    if (a > 20 || b > 20 || c > 20) return w(20, 20, 20);
    if (dp[a][b][c].has_value()) return dp[a][b][c].value();

    if (a < b && b < c)
        dp[a][b][c].emplace(w(a, b, c - 1) + w(a, b - 1, c - 1) -
                            w(a, b - 1, c));
    else
        dp[a][b][c].emplace(w(a - 1, b, c) + w(a - 1, b - 1, c) +
                            w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1));
                            
    return dp[a][b][c].value();
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int a, b, c;
    while (std::cin >> a >> b >> c && (a != -1 || b != -1 || c != -1))
        std::cout << "w(" << a << ", " << b << ", " << c << ") = " << w(a, b, c)
                  << '\n';

    return 0;
}
