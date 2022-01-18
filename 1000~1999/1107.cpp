#include <algorithm>
#include <iostream>
#include <vector>

bool isValid(int x, const std::vector<int>& broken) {
    do {
        if (std::binary_search(broken.cbegin(), broken.cend(), x % 10))
            return false;

        x /= 10;
    } while (x);

    return true;
}

int numLength(int x) {
    int length = 0;
    do {
        x /= 10;
        ++length;
    } while (x);

    return length;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> broken(m);
    for (auto& i : broken) std::cin >> i;

    std::sort(broken.begin(), broken.end());

    int min = (100 < n ? n - 100 : 100 - n);
    for (int i = 0; i < n + min; ++i)
        if (int curClick = (i < n ? n - i : i - n) + numLength(i);
            isValid(i, broken) && curClick < min)
            min = curClick;

    std::cout << min;

    return 0;
}