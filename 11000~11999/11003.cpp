#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, L;
    std::cin >> N >> L;

    std::deque<std::pair<int, int>> dq;

    for (int i = 0; i < N; ++i) {
        int A;
        std::cin >> A;

        while (!dq.empty() && dq.front().second < i - L + 1)
            dq.pop_front();
        
        while (!dq.empty() && dq.back().first > A)
            dq.pop_back();

        dq.push_back({A, i});
        std::cout << dq.front().first << ' ';
    }
    
    return 0;
}