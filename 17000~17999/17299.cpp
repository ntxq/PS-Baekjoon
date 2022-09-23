#include <iostream>
#include <stack>
#include <vector>

const int SIZE = 1000000;

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> A(N);
    std::vector<int> count(1000000);

    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
        ++count[A[i]];
    }

    std::stack<int> NGF;
    std::stack<int> result;
    while (!A.empty()) {
        int a = A.back();
        A.pop_back();

        while (!NGF.empty() && count[NGF.top()] <= count[a]) NGF.pop();

        if (NGF.empty())
            result.push(-1);
        else
            result.push(NGF.top());
        NGF.push(a);
    }

    while (!result.empty()) {
        std::cout << result.top() << ' ';
        result.pop();
    }

    return 0;
}