#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr);

    int size;
    std::cin >> size;

    for (int i = 0; i < size; ++i) {
        std::string s;
        std::cin >> s;

        int count = 0;
        for (unsigned j = 0; count >= 0 && j < s.size(); ++j)
            if (s[j] == '(')
                ++count;
            else
                --count;

        std::cout << (count == 0 ? "YES\n" : "NO\n");
    }

    return 0;
}