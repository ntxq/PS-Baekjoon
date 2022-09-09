#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        std::string input;
        std::cin >> input;

        bool isPalindrome = true;
        int count = 0;

        for (unsigned i = 0; i * 2 <= input.size(); ++i, ++count)
            if (input[i] != input[input.size() - i - 1]) {
                isPalindrome = false;
                break;
            }

        std::cout << isPalindrome << ' ' << (count + !isPalindrome) << '\n';
    }

    return 0;
}