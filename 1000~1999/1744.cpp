
#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::priority_queue<int> positives;
    std::priority_queue<int> ones;
    std::priority_queue<int> zeros;
    std::priority_queue<int, std::vector<int>, std::greater<int>> negatives;

    int N;
    std::cin >> N;

    for (int i = 0; i < N; ++i) {
        int x;
        std::cin >> x;
        if (x > 1)
            positives.push(x);
        else if (x == 1)
            ones.push(x);
        else if (x == 0)
            zeros.push(x);
        else
            negatives.push(x);
    }

    int sum = 0;

    while (positives.size() > 1) {
        int a = positives.top();
        positives.pop();
        int b = positives.top();
        positives.pop();
        sum += a * b;
    }
    while (!positives.empty()) {
        sum += positives.top();
        positives.pop();
    }

    while (!ones.empty()) {
        sum += ones.top();
        ones.pop();
    }

    while (negatives.size() > 1) {
        int a = negatives.top();
        negatives.pop();
        int b = negatives.top();
        negatives.pop();
        sum += a * b;
    }

    if (negatives.size() == 1 && !zeros.empty()) {
        negatives.pop();
        zeros.pop();
    }

    while (!negatives.empty()) {
        sum += negatives.top();
        negatives.pop();
    }

    std::cout << sum << '\n';

    return 0;
}
