#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, A, B;
    std::cin >> N >> A >> B;

    if (A < B)
        std::cout << "Bus\n";
    else if (A > B)
        std::cout << "Subway\n";
    else
        std::cout << "Anything\n";

    return 0;
}
