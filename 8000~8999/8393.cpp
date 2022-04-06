#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    int sum = 0;
    for (int i = 1; i <= n; ++i)
        sum += i;

    std::cout << sum << '\n';

    return 0;
}
