#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<int> A(N);
    for (int& i : A) std::cin >> i;

    std::vector<int> B(M);
    for (int& i : B) std::cin >> i;

    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());

    std::vector<int> C;
    std::set_symmetric_difference(A.begin(), A.end(), B.begin(), B.end(),
                                  std::back_inserter(C));

    std::cout << C.size() << '\n';

    return 0;
}