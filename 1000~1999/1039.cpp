#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <vector>

int findMaxString(const std::string& n, int k) {
    std::queue<std::pair<std::string, int>> q;
    std::map<std::string, int> visited;

    q.push({n, 0});
    visited.insert({n, 0});

    int maxInt = -1;
    while (!q.empty()) {
        auto [curStr, d] = q.front();
        q.pop();

        if (d == k) {
            maxInt = std::max(maxInt, std::stoi(curStr));
            continue;
        }

        for (int i = 0; i < curStr.size(); ++i) {
            for (int j = i + 1; j < curStr.size(); ++j) {
                std::string nextStr = curStr;
                std::swap(nextStr[i], nextStr[j]);

                if (nextStr[0] == '0') continue;
                if (visited[nextStr] > d) continue;

                q.push({nextStr, d + 1});
                visited[nextStr] = d + 1;
            }
        }
    }

    return maxInt;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string N;
    int K;
    std::cin >> N >> K;

    std::cout << findMaxString(N, K) << '\n';

    return 0;
}
