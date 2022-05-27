#include <algorithm>
#include <iostream>
#include <queue>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, K;
    std::cin >> N >> K;

    std::queue<int> Q;
    for (int i = 1; i <= N; ++i) Q.push(i);

   std::queue<int> S;
    while (!Q.empty()) {
        for (int i = 0; i < K - 1; ++i) {
            Q.push(Q.front());
            Q.pop();
        }

        S.push(Q.front());
        Q.pop();
    }

    std::cout << '<';
    while (S.size() > 1) {
        std::cout << S.front() << ", ";
        S.pop();
    }
    std::cout << S.front() << '>';

    return 0;
}