#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::deque<int> q;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        q.push_back(x);
    }
    std::sort(q.begin(), q.end());

    long long total = 0;
    std::deque<int> expr;

    expr.push_back(q.back());
    q.pop_back();

    while (!q.empty()) {
        int ll = std::abs(q.front() - expr.front());
        int lr = std::abs(q.front() - expr.back());
        int rl = std::abs(q.back() - expr.front());
        int rr = std::abs(q.back() - expr.back());

        int maxDiff = std::max({ll, lr, rl, rr});
        total += maxDiff;
        if (maxDiff == ll) {
            expr.push_front(q.front());
            q.pop_front();
        } else if (maxDiff == lr) {
            expr.push_back(q.front());
            q.pop_front();
        } else if (maxDiff == rl) {
            expr.push_front(q.back());
            q.pop_back();
        } else {
            expr.push_back(q.back());
            q.pop_back();
        }
    }

    std::cout << total << '\n';

    return 0;
}
