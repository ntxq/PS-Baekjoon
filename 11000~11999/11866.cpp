#include <deque>
#include <iostream>
#include <numeric>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, k;
    std::cin >> n >> k;

    std::deque<int> q(n);
    std::iota(q.begin(), q.end(), 1);

    std::cout << '<';
    for (int i = 1 % k; q.size() > 1; i = (i + 1) % k) {
        int x = q.front();
        q.pop_front();

        if (i)
            q.push_back(x);
        else
            std::cout << x << ", ";
    }
    std::cout << q.front() << '>';

    return 0;
}