#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string s;
    std::cin >> s;

    std::cout << std::equal(s.begin(), s.end(), s.rbegin()) << '\n';

    return 0;
}
