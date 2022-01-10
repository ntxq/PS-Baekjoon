#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned long long padovan[100]{1, 1, 1};
    for (int i = 3; i < 100; ++i) padovan[i] = padovan[i - 2] + padovan[i - 3];

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        int n;
        std::cin >> n;

        std::cout << padovan[n - 1] << '\n';
    }

    return 0;
}