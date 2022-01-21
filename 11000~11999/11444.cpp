#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

void multiply(unsigned long long a[2][2], unsigned long long b[2][2]) {
    unsigned long long i = a[0][0] * b[0][0] + a[0][1] * b[1][0];
    unsigned long long j = a[0][0] * b[0][1] + a[0][1] * b[1][1];
    unsigned long long k = a[1][0] * b[0][0] + a[1][1] * b[1][0];
    unsigned long long l = a[1][0] * b[0][1] + a[1][1] * b[1][1];

    a[0][0] = i % 1000000007;
    a[0][1] = j % 1000000007;
    a[1][0] = k % 1000000007;
    a[1][1] = l % 1000000007;
}

void power(unsigned long long matrix[2][2], unsigned long long n) {
    if (n < 2) return;

    power(matrix, n / 2);
    multiply(matrix, matrix);

    unsigned long long m[2][2]{{1, 1}, {1, 0}};
    if (n % 2) multiply(matrix, m);
}

unsigned long long fibo(unsigned long long n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    unsigned long long result[2][2]{{1, 1}, {1, 0}};
    power(result, n - 1);

    return result[0][0];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned long long n;
    std::cin >> n;

    std::cout << fibo(n);

    return 0;
}