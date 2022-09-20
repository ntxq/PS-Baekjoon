#include <iostream>

constexpr int MOD = 10007;

template <int N>
struct Combination {
    constexpr Combination() : arr() {
        for (int i = 0; i < N; i++) {
            arr[i][0] = 1;
            arr[i][i] = 1;
            for (int j = 1; j < i; j++)
                arr[i][j] = arr[i][i - j] =
                    (arr[i - 1][j - 1] + arr[i - 1][j]) % MOD;
        }
    }

    int arr[N][N];
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    constexpr Combination<53> nCk;

    int N;
    std::cin >> N;

    int ans = 0;
    for (int i = 4; i <= N; i += 4)
        if ((i / 4) % 2 == 1)
            ans = (ans + nCk.arr[13][i / 4] * nCk.arr[52 - i][N - i]) % MOD;
        else
            ans = (ans - nCk.arr[13][i / 4] * nCk.arr[52 - i][N - i]) % MOD;

    std::cout << (ans + MOD) % MOD << '\n';

    return 0;
}