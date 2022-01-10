#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int tiles[1000]{1, 3};
    for (int i = 2; i < 1000; ++i)
        tiles[i] = (tiles[i - 1] + 2 * tiles[i - 2]) % 10007;

    int n;
    std::cin >> n;

    std::cout << tiles[n - 1];

    return 0;
}