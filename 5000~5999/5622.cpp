#include <algorithm>
#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string s;
    std::cin >> s;

    int count = 0;
    for (char c : s) {
        if (c < 'D')
            count += 3;
        else if (c < 'G')
            count += 4;
        else if (c < 'J')
            count += 5;
        else if (c < 'M')
            count += 6;
        else if (c < 'P')
            count += 7;
        else if (c < 'T')
            count += 8;
        else if (c < 'W')
            count += 9;
        else
            count += 10;
    }

    std::cout << count << '\n';

    return 0;
}
