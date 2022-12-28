#include <iostream>
#include <queue>
#include <set>
#include <string>

std::string bfs(int s, int t) {
    if (s == t) return "0";

    std::queue<std::pair<long long, std::string>> q;
    std::set<int> visited;

    q.push({s, ""});
    visited.insert(s);

    while (!q.empty()) {
        auto [u, ops] = q.front();
        q.pop();

        if (u == t) return ops;

        if (auto prod = u * u; prod <= t && !visited.contains(prod)) {
            q.push({prod, ops + '*'});
            visited.insert(prod);
        }

        if (auto sum = u + u; sum <= t && !visited.contains(sum)) {
            q.push({sum, ops + '+'});
            visited.insert(sum);
        }

        if (!visited.contains(0)) {
            q.push({0, ops + '-'});
            visited.insert(0);
        }

        if (u && !visited.contains(1)) {
            q.push({1, ops + '/'});
            visited.insert(1);
        }
    }

    return "-1";
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int s, t;
    std::cin >> s >> t;

    std::cout << bfs(s, t) << '\n';

    return 0;
}
