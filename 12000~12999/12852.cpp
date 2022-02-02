#include <iostream>
#include <queue>
#include <stack>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> prev(n + 1);
    std::queue<int> q;

    prev[n] = n;
    q.push(n);

    int count = 0;
    while (!prev[1]) {
        int curSize = q.size();

        for (int i = 0; i < curSize; ++i) {
            int cur = q.front();
            q.pop();

            if (!(cur % 3) && !prev[cur / 3]) {
                prev[cur / 3] = cur;
                q.push(cur / 3);
            }

            if (!(cur % 2) && !prev[cur / 2]) {
                prev[cur / 2] = cur;
                q.push(cur / 2);
            }

            if (!prev[cur - 1]) {
                prev[cur - 1] = cur;
                q.push(cur - 1);
            }
        }

        ++count;
    }

    std::stack<int> s;
    for (int i = 1; i != n; i = prev[i]) s.push(i);
    s.push(n);

    std::cout << count << '\n';
    while (!s.empty()) {
        std::cout << s.top() << ' ';
        s.pop();
    }

    return 0;
}