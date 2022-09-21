#include <iostream>
#include <stack>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    long long count = 0;
    std::stack<std::pair<long long, int>> S;

    for (int i = 0; i < N; ++i) {
        long long height;
        std::cin >> height;

        int duplicate = 1;
        while (!S.empty() && S.top().first <= height) {
            count += S.top().second;

            if (S.top().first == height) duplicate = S.top().second + 1;
            S.pop();
        }

        if (!S.empty()) ++count;
        S.push({height, duplicate});
    }

    std::cout << count << '\n';

    return 0;
}