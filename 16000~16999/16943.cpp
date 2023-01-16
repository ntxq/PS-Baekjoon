#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int A, B;
    std::cin >> A >> B;

    std::string C = std::to_string(A);
    std::sort(C.begin(), C.end());

    int max = -1;
    do {
        int num = std::stoi(C);
        if (num < B && C[0] != '0') max = num;
    } while (std::next_permutation(C.begin(), C.end()));

    std::cout << max << '\n';

    return 0;
}