#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    int steps = 1;
    for (int sum = 1; sum < n; sum += 6 * steps++)
        ;

    std::cout << steps;

    return 0;
}