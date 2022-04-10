#include <algorithm>
#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string A, B;
    std::cin >> A >> B;
    if (A.size() < B.size()) std::swap(A, B);

    int carry = 0;
    std::string C;
    for (auto a = A.rbegin(), b = B.rbegin(); a != A.rend(); ++a) {
        int sum = (*a - '0') + carry;
        if (b != B.rend()) {
            sum += (*b - '0');
            ++b;
        }

        carry = sum / 10;
        sum %= 10;

        C.push_back(sum + '0');
    }

    if (carry) C.push_back(carry + '0');

    std::cout << std::string(C.rbegin(), C.rend());

    return 0;
}
