#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> is_stack(N);
    for (int& i : is_stack) std::cin >> i;

    std::vector<int> elements(N);
    for (int& i : elements) std::cin >> i;

    std::queue<int> queue;
    for (int i = N - 1; i >= 0; --i)
        if (!is_stack[i]) queue.push(elements[i]);

    int M;
    std::cin >> M;

    for (int i = 0; i < M; ++i) {
        int x;
        std::cin >> x;

        queue.push(x);
        std::cout << queue.front() << ' ';
        queue.pop();
    }

    std::cout << '\n';

    return 0;
}