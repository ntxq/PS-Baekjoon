#include <iostream>
#include <stack>
#include <string>
#include <vector>

std::stack<char> lcs(const std::string& a, const std::string& b) {
    std::vector<std::vector<int>> dp(a.size() + 1,
                                     std::vector<int>(b.size() + 1, 0));

    for (unsigned i = 1; i <= a.size(); ++i)
        for (unsigned j = 1; j <= b.size(); ++j)
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);

    std::stack<char> st;
    for (int i = a.size(), j = b.size(); i > 0 && j > 0;) {
        if (a[i - 1] == b[j - 1]) {
            st.push(a[i - 1]);
            --i;
            --j;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }

    return st;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string a, b;
    std::cin >> a >> b;

    std::stack<char> st = lcs(a, b);
    std::cout << st.size() << '\n';
    while (!st.empty()) {
        std::cout << st.top();
        st.pop();
    }

    return 0;
}