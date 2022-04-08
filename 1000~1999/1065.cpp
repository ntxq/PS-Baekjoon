#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

bool isArithmetic(int x) {
    int diff = (x % 10) - ((x / 10) % 10);
    while (x > 9) {
        int curDiff = (x % 10) - ((x / 10) % 10);
        if (curDiff != diff) return false;
        x /= 10;
    }

    return true;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    int count = 0;
    for (int i = 1; i <= N; ++i)
        if (isArithmetic(i)) ++count;

    std::cout << count << '\n';

    return 0;
}
