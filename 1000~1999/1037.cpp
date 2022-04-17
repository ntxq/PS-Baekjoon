#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    int min = 0;
    int max = 0;
    for (int i = 0; i < N; ++i) {
        int factor;
        std::cin >> factor;

        if (factor < min || !min) min = factor;
        if (factor > max || !max) max = factor;
    }

    std::cout << min * max << '\n';

    return 0;
}
