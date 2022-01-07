#include <iostream>
#include <stack>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int k;
    std::cin >> k;

    std::stack<int> sum;
    for (int i = 0; i < k; ++i) {
        int num;
        std::cin >> num;

        if (sum.empty())
            sum.push(num);
        else if (num)
            sum.push(num + sum.top());
        else
            sum.pop();
    }

    std::cout << (sum.empty() ? 0 : sum.top());

    return 0;
}