#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> H(N);
    for (auto& i : H) std::cin >> i;

    int area = 0;
    std::stack<int> S;
    for (int i = 0; i <= N; ++i) {
        while (!S.empty() && H[S.top()] > H[i]) {
            int h = H[S.top()];
            S.pop();

            int l = S.empty() ? 0 : S.top() + 1;
            area = std::max(area, h * (i - l));
        }
        S.push(i);
    }

    while (!S.empty()) {
        int h = H[S.top()];
        S.pop();

        int l = S.empty() ? 0 : S.top() + 1;
        area = std::max(area, h * (N - l));
    }

    std::cout << area << '\n';

    return 0;
}