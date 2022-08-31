#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int X;
    int N;
    std::cin >> X >> N;

    int sum = 0;
    for (int i = 0; i < N; ++i) {
        int a, b;
        std::cin >> a >> b;
        sum += a * b;
    }

    std::cout << (sum == X ? "Yes" : "No") << '\n';

    return 0;
}