#include <algorithm>
#include <iostream>

int main() {
    int x, y, z;
    while ((std::cin >> x >> y >> z), x || y || z) {
        const int& max = std::max({x, y, z});
        if (x * x + y * y + z * z - 2 * max * max)
            std::cout << "wrong\n";
        else
            std::cout << "right\n";
    }

    return 0;
}