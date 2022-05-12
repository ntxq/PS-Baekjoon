#include <algorithm>
#include <cmath>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int K;
    std::cin >> K;

    int box[6];
    for (int i = 0; i < 6; ++i) std::cin >> box[i] >> box[i];

    int w = 0, h = 0;
    for (int i = 0; i < 3; ++i) {
        if (w < box[2 * i]) w = box[2 * i];
        if (h < box[2 * i + 1]) h = box[2 * i + 1];
    }

    int ww, hh;

    for (int i = 0; i < 6; ++i) {
        if (box[(i + 5) % 6] + box[(i + 1) % 6] == w) hh = box[i];
        if (box[(i + 5) % 6] + box[(i + 1) % 6] == h) ww = box[i];
    }

    std::cout << (h * w - ww * hh) * K << '\n';

    return 0;
}