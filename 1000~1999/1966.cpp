#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        int n, x;
        std::cin >> n >> x;

        std::priority_queue<int> pq;
        std::queue<std::pair<int, int>> q;

        for (int j = 0; j < n; ++j) {
            int a;
            std::cin >> a;

            pq.push(a);
            q.push({j, a});
        }

        int order = 0;
        bool flag = false;
        while (!flag) {
            auto [idx, val] = q.front();
            q.pop();

            if (val == pq.top()) {
                if (idx == x) flag = true;
                pq.pop();
                ++order;

            } else {
                q.push({idx, val});
            }
        }

        std::cout << order << '\n';
    }

    return 0;
}