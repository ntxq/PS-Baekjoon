#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    int bags = -1;
    for (int i = 0; i * 5 <= n; ++i)
        if (int tmp = (n - i * 5) / 3; 5 * i + 3 * tmp == n)
            if (tmp + i < bags || bags == -1) bags = tmp + i;

    std::cout << bags;

    return 0;
}