#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int& i : a) std::cin >> i;

    std::vector<int> lis(n, 1);
    std::vector<int> lds(n, 1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j)
            if (a[j] < a[i] && lis[j] + 1 > lis[i]) lis[i] = lis[j] + 1;

        for (int j = n - 1; j > n - i - 1; --j)
            if (a[j] < a[n - i - 1] && lds[j] + 1 > lds[n - i - 1])
                lds[n - i - 1] = lds[j] + 1;
    }

    int ans = 0;
    for (int i = 0; i < n; ++i)
        if (lis[i] + lds[i] - 1 > ans) ans = lis[i] + lds[i] - 1;

    std::cout << ans;

    return 0;
}