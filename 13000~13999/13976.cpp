#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

typedef std::array<std::array<long long, 2>, 2> Matrix;
const long long mod = 1000000007;

Matrix matrixMultiply(Matrix A, Matrix B) {
    Matrix C{};
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
                C[i][j] = (C[i][j] + (A[i][k] * B[k][j] + mod) % mod) % mod;

    return C;
}

Matrix matrixPower(Matrix Base, long long exp) {
    Matrix result{1, 0, 0, 1};
    while (exp) {
        if (exp % 2) result = matrixMultiply(result, Base);

        Base = matrixMultiply(Base, Base);
        exp /= 2;
    }

    return result;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    long long N;
    std::cin >> N;

    Matrix base = {4, -1, 1, 0};
    Matrix answer = {3, 0, 1, 0};

    base = matrixPower(base, N / 2);
    answer = matrixMultiply(base, answer);

    if (N % 2)
        std::cout << 0 << '\n';
    else
        std::cout << answer[1][0] << '\n';

    return 0;
}