#include <algorithm>
#include <iostream>
#include <limits>
#include <stack>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    while (std::cin >> n && n) {
        unsigned long long maxRect = 0;

        std::vector<unsigned long long> hist(n);
        for (unsigned long long& h : hist) std::cin >> h;

        std::stack<unsigned long long> s;
        for (int i = 0; i < n; ++i) {
            if (s.empty() || hist[s.top()] < hist[i]) {
                s.push(i);
            } else {
                while (!s.empty() && hist[s.top()] > hist[i]) {
                    int curMin = s.top();
                    s.pop();

                    int left = s.empty() ? 0 : s.top() + 1;
                    int right = i - 1;

                    unsigned long long curRect =
                        hist[curMin] * (right - left + 1);
                    if (curRect > maxRect) maxRect = curRect;
                }

                s.push(i);
            }
        }

        while (!s.empty()) {
            int curMin = s.top();
            s.pop();

            int left = s.empty() ? 0 : s.top() + 1;
            int right = n - 1;

            unsigned long long curRect = hist[curMin] * (right - left + 1);
            if (curRect > maxRect) maxRect = curRect;
        }

        std::cout << maxRect << '\n';
    }

    return 0;
}
