#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    int len = (n / 4) + (n % 4);
    for (int i = 0; i < len; ++i)
        std::cout << "long ";
    std::cout << "int\n";

    return 0;
}
