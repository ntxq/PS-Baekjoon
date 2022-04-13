#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> A(N);
    for (int& i : A) std::cin >> i;

    std::sort(A.begin(), A.end());
    for (int i : A) std::cout << i << '\n';

    return 0;
}
