#include <iostream>
#include <string>

int main() {
    std::string str;
    std::cin >> str;

    int alpha[26] = {};

    for (unsigned i = 0; i < str.size(); ++i)
        if (!alpha[str[i] - 'a']) alpha[str[i] - 'a'] = i + 1;

    for (const int& i : alpha) std::cout << i - 1 << ' ';

    return 0;
}