#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int params[6];
    for (int i = 0; i < 6; ++i) std::cin >> params[i];

    for (int i = -999; i < 1000; ++i)
        for (int j = -999; j < 1000; ++j)
            if (params[0] * i + params[1] * j == params[2] &&
                params[3] * i + params[4] * j == params[5])
                std::cout << i << ' ' << j << '\n';

    return 0;
}
