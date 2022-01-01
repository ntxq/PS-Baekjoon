#include <iostream>

template <int N>
struct Factorial {
    constexpr Factorial() : arr() {
        for (int i = 0; i < N; ++i) arr[i] = i ? arr[i - 1] * i : 1;
    }

    int arr[N];
};

int main() {
    constexpr Factorial<11> fact;

    int n, k;
    std::cin >> n >> k;

    std::cout << fact.arr[n] / (fact.arr[k] * fact.arr[n - k]);

    return 0;
}