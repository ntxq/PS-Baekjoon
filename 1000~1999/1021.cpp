#include <algorithm>
#include <deque>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::deque<int> dq;
    for (int i = 1; i <= N; ++i) dq.push_back(i);

    int count = 0;
    for (int i = 0; i < M; ++i) {
        int p;
        std::cin >> p;

        int leftDist = 1;
        for (auto it = dq.rbegin(); it != dq.rend() && *it != p; ++it)
            ++leftDist;

        int rightDist = 0;
        for (auto it = dq.begin(); it != dq.end() && *it != p; ++it)
            ++rightDist;

        if (leftDist < rightDist) {
            count += leftDist;
            while (leftDist--) {
                dq.push_front(dq.back());
                dq.pop_back();
            }
        } else {
            count += rightDist;
            while (rightDist--) {
                dq.push_back(dq.front());
                dq.pop_front();
            }
        }
        dq.pop_front();
    }

    std::cout << count << '\n';

    return 0;
}