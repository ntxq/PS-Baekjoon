#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string A, B;
    std::cin >> A >> B;

    std::vector<int> count(26, 0);

    int i = B.size() - 1;
    int ops = 0;

    for (int j = A.size() - 1; j >= 0; --j) {
        if (B[i] == A[j])
            --i;
        else {
            ++count[A[j] - 'A'];
            ++ops;
        }
    }

    while (i >= 0) --count[B[i--] - 'A'];

    bool isValid =
        std::all_of(count.begin(), count.end(), [](int c) { return c == 0; });

    if (isValid)
        std::cout << ops << '\n';
    else
        std::cout << "-1\n";

    return 0;
}
