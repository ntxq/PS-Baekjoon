#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    int shirts[6];
    for (int& shirt : shirts) std::cin >> shirt;

    int T, P;
    std::cin >> T >> P;

    int shirtsCnt = 0;
    for (int shirt : shirts) shirtsCnt += (shirt / T) + (shirt % T != 0);

    std::cout << shirtsCnt << '\n' << N / P << ' ' << N % P << '\n';

    return 0;
}
