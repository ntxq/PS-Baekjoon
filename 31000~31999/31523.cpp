#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

int dfs(int u, int p, std::vector<char>& stack,
        const std::vector<std::vector<int>>& adj, const std::string& parens) {
    char cur = parens[u - 1];

    int cnt = 0;
    if (cur == '(' || cur == '[' || cur == '{') {
        stack.push_back(cur);

        for (int v : adj[u]) {
            if (v == p) continue;
            cnt += dfs(v, u, stack, adj, parens);
        }

        stack.pop_back();
    } else if (stack.empty() ||
               (stack.back() != cur - 1 && stack.back() != cur - 2)) {
        cnt = 0;
    } else {
        stack.pop_back();

        if (stack.empty()) ++cnt;
        for (int v : adj[u]) {
            if (v == p) continue;
            cnt += dfs(v, u, stack, adj, parens);
        }

        stack.push_back(cur - 1);
    }

    return cnt;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::string parens;
    std::cin >> parens;

    std::vector<std::vector<int>> adj(N + 1);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int cnt = 0;
    std::vector<char> stack;
    for (int i = 1; i <= N; ++i) cnt += dfs(i, 0, stack, adj, parens);

    std::cout << cnt << '\n';

    return 0;
}
