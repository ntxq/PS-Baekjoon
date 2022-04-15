#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    int a = 1;
    int b = 2;
    for (int i = 2; i <= N; ++i) {
        int c = (a + b) % 15746;
        a = b;
        b = c;
    }

    std::cout << a << '\n';

    return 0;
}
