#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int t = 0; t < T; ++t) {
        int N, M;
        std::cin >> N >> M;

        for (int i = 0; i < M; ++i) {
            int a, b;
            std::cin >> a >> b;
        }

        std::cout << N - 1 << '\n';
    }

    return 0;
}