#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    long long prev = 0;
    long long cur = 1;

    while (--N) {
        long long next = prev + cur;
        prev = cur;
        cur = next;
    }

    std::cout << cur;

    return 0;
}