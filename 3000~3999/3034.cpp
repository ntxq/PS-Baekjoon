#include <algorithm>
#include <iostream>
#include <cmath>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, W, H;
    std::cin >> N >> W >> H;

    double limit = std::hypot(W, H);
    for (int i = 0; i < N; ++i) {
        int l;
        std::cin >> l;

        if (l <= limit)
            std::cout << "DA" << '\n';
        else
            std::cout << "NE" << '\n';
    }

    return 0;
}