#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int a, b;
        std::cin >> a >> b;
        a %= 10;

        int result = 1;
        while (b) { 
            if (b % 2)
                result = (result * a) % 10;
            
            a = (a * a) % 10;
            b /= 2;
        }

        std::cout << (result == 0 ? 10 : result) << '\n';
    }

    return 0;
}