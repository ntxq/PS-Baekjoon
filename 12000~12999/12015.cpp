#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> seq(n);
    for (int& i : seq) std::cin >> i;

    std::vector<int> lis;
    for (int i = 0; i < n; ++i) {
        auto it = std::lower_bound(lis.begin(), lis.end(), seq[i]);

        if (it == lis.end()) lis.push_back(seq[i]);
        else *it = seq[i];
    }

    std::cout << lis.size() << '\n';

    return 0;
}