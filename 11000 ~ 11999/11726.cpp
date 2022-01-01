#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int size;
    std::cin >> size;

    std::vector<int> fibo(size);
    fibo[0] = 1;
    fibo[1] = 2;

    for (int i = 2; i < size; ++i)
        fibo[i] = (fibo[i - 1] + fibo[i - 2]) % 10007;

    std::cout << fibo[size - 1];

    return 0;
}