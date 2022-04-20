#include <algorithm>
#include <iostream>
#include <stack>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::stack<int> A;
    for (int i = 0; i < N; ++i) {
        int a;
        std::cin >> a;

        A.push(a);
    }

    std::stack<int> NGE;
    std::stack<int> result;
    while (!A.empty()) {
        int a = A.top();
        A.pop();

        while (!NGE.empty() && NGE.top() <= a) NGE.pop();

        if (NGE.empty())
            result.push(-1);
        else
            result.push(NGE.top());
        NGE.push(a);
    }

    while (!result.empty()) {
        std::cout << result.top() << '\n';
        result.pop();
    }

    return 0;
}
