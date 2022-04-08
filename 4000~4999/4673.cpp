#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

int generate(int x) {
    int sum = x;
    while (x > 0) {
        sum += x % 10;
        x /= 10;
    }

    return sum < 10001 ? sum : 0;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<bool> isGenerated(10001);
    for (int i = 1; i < 10001; ++i) {
        isGenerated[generate(i)] = true;
        if (!isGenerated[i])
            std::cout << i << '\n';
    }

    return 0;
}
