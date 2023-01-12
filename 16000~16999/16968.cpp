#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string s;
    std::cin >> s;

    int count = 1;
    char prev = '\0';
    for (auto c : s)
        if (c == 'd' && c == prev)
            count *= 9;
        else if (c == 'c' && c == prev)
            count *= 25;
        else if ((prev = c) == 'd')
            count *= 10;
        else if ((prev = c) == 'c')
            count *= 26;

    std::cout << count << '\n';

    return 0;
}