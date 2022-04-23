#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::priority_queue<int> maxPQ;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minPQ;

    int median;
    std::cin >> median;
    std::cout << median << '\n';
    maxPQ.push(median);

    for (int i = 1; i < N; ++i) {
        int x;
        std::cin >> x;

        if (x < median)
            maxPQ.push(x);
        else
            minPQ.push(x);

        if (minPQ.size() >= maxPQ.size() + 1) {
            maxPQ.push(minPQ.top());
            minPQ.pop();
        } else if (maxPQ.size() > minPQ.size() + 1) {
            minPQ.push(maxPQ.top());
            maxPQ.pop();
        }

        median = maxPQ.top();
        std::cout << median << '\n';
    }

    return 0;
}