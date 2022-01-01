#include <iostream>
#include <string>

int main() {
    std::string s;
    while ((std::cin >> s), s != "0") {
        bool palindrome = true;
        for (unsigned i = 0, j = s.size() - 1; i < j; ++i, --j)
            if (s[i] != s[j]) {
                palindrome = false;
                break;
            }

        std::cout << (palindrome ? "yes\n" : "no\n");
    }

    return 0;
}