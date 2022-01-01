#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    int home[15][15]{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}};

    for (int i = 1; i < 15; ++i)
        for (int j = 0; j < 15; ++j)
            if (j == 0)
                home[i][j] = 1;
            else
                home[i][j] = home[i - 1][j] + home[i][j - 1];

    for (int i = 0; i < t; ++i) {
        int k, n;
        std::cin >> k >> n;

        std::cout << home[k][n - 1] << '\n';
    }

    return 0;
}