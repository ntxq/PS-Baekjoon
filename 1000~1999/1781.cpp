#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::priority_queue<std::pair<int, int>> deadlines;
    for (int i = 0; i < N; ++i) {
        int a, b;
        std::cin >> a >> b;

        deadlines.push({-a, b});
    }

    int curTime = 0;
    std::priority_queue<int> tasks;
    while (!deadlines.empty()) {
        auto [time, value] = deadlines.top();
        deadlines.pop();
        time = -time;

        if (curTime < time) {
            tasks.push(-value);
            ++curTime;
        } else if (-tasks.top() < value) {
            tasks.pop();
            tasks.push(-value);
        }
    }

    int sum = 0;
    while (!tasks.empty()) {
        sum -= tasks.top();
        tasks.pop();
    }
    std::cout << sum << '\n';

    return 0;
}
