#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    int factorial = 1;
    while (N)
        factorial *= N--;

    std::cout << factorial << '\n';

    return 0;
}
