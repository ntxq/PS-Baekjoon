#include <iostream>
#include <vector>

template <int N>
class FiboCount {
   public:
    constexpr FiboCount() {
        for (int i = 2; i < N; ++i) {
            zeroCount[i] = zeroCount[i - 1] + zeroCount[i - 2];
            oneCount[i] = oneCount[i - 1] + oneCount[i - 2];
        }
    }

    unsigned long long zeroCount[N] = {1};
    unsigned long long oneCount[N] = {0, 1};
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    FiboCount<41> fibo;

    int cases;
    std::cin >> cases;

    for (int i = 0; i < cases; ++i) {
        int x;
        std::cin >> x;

        std::cout << fibo.zeroCount[x] << ' ' << fibo.oneCount[x] << '\n';
    }

    return 0;
}