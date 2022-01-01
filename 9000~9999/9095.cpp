#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int countExpression(int x) {
    static int counts[11]{0, 1, 2, 4};

    if (x <= 0) return 0;
    if (counts[x]) return counts[x];

    counts[x] = countExpression(x - 3) + countExpression(x - 2) +
                countExpression(x - 1);
    return counts[x];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int size;
    std::cin >> size;

    for (int i = 0; i < size; ++i) {
        int x;
        std::cin >> x;
        std::cout << countExpression(x) << '\n';
    }

    return 0;
}