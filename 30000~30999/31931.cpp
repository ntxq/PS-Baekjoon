#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        long long X, Y, A, B, C, D;
        std::cin >> X >> Y >> A >> B >> C >> D;

        if (Y <= A) {
            std::cout << "NARUTO\n";
            continue;
        }

        if (X + B <= C) {
            std::cout << "SASUKE\n";
            continue;
        }

        if (A > D) {
            if (B > C) {
                std::cout << "NARUTO\n";
                continue;
            } else {
                long long sTime = (X + C - 1) / C;
                if (static_cast<__int128_t>(sTime) *
                        static_cast<__int128_t>(A) >=
                    static_cast<__int128_t>(Y)) {
                    std::cout << "NARUTO\n";
                    continue;
                }
            }
        }
        if (C > B) {
            if (D > A) {
                std::cout << "SASUKE\n";
                continue;
            } else {
                long long nTime = (Y + A - 1) / A;
                if (static_cast<__int128_t>(nTime - 1) *
                        static_cast<__int128_t>(C) >=
                    static_cast<__int128_t>(X)) {
                    std::cout << "SASUKE\n";
                    continue;
                }
            }
        }

        std::cout << "DRAW\n";
    }

    return 0;
}
