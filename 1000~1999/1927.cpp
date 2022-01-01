#include <functional>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int cases;
    std::cin >> cases;

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int x; std::cin >> x;) {
        if (x)
            pq.push(x);
        else if (pq.size()) {
            std::cout << pq.top() << '\n';
            pq.pop();
        } else
            std::cout << 0 << '\n';
    }

    return 0;
}