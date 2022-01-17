#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;
    for (int i = 0; i < n; ++i) {
        int input;
        std::cin >> input;

        if (input < 0)
            pq.push({-input, input});
        else if (input > 0)
            pq.push({input, input});
        else if (pq.empty())
            std::cout << "0\n";
        else {
            std::cout << pq.top().second << '\n';
            pq.pop();
        }
    }

    return 0;
}