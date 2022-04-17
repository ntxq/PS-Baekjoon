#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int a, b;
    while (std::cin >> a >> b && (a || b)) {
        if (b % a == 0)
            std::cout << "factor" << '\n';
        else if (a % b == 0)
            std::cout << "multiple" << '\n';
        else
            std::cout << "neither" << '\n';
    }

    return 0;
}
