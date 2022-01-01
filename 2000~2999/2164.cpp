#include <iostream>
#include <queue>

int main() {
    std::cin.tie(nullptr);

    int size;
    std::cin >> size;

    std::queue<int> q;
    for (int i = 0; i < size; ++i) {
        q.push(i);
    }

    while (q.size() > 1) {
        q.pop();
        q.push(q.front());
        q.pop();
    }

    std::cout << q.front() + 1;

    return 0;
}