#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;
    int* A = new int[n * m];

    for (int i = 0; i < n * m; ++i) std::cin >> A[i];

    int k;
    std::cin >> m >> k;
    int* B = new int[m * k];

    for (int i = 0; i < m * k; ++i) std::cin >> B[i];

    int* C = new int[n * k];
    for (int i = 0; i < n * k; ++i) {
        C[i] = 0;
        for (int j = 0; j < m; ++j) C[i] += A[i / k * m + j] * B[j * k + i % k];

        std::cout << C[i] << " ";
        if (i % k == k - 1) std::cout << "\n";
    }

    return 0;
}