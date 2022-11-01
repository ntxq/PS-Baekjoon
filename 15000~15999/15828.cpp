#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::queue<int> q;

    int input;
    while (std::cin >> input, input != -1)
        if (input == 0)
            q.pop();
        else if (q.size() < n)
            q.push(input);

    if (q.empty())
        std::cout << "empty";
    else
        while (!q.empty()) std::cout << q.front() << ' ', q.pop();
    std::cout << '\n';

    return 0;
}