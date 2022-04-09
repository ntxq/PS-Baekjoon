#include <algorithm>
#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string s;
    std::cin >> s;

    int count = 0;
    for (unsigned i = 0; i < s.size(); ++i) {
        if (i + 2 < s.size() && s[i] == 'd' && s[i + 1] == 'z' &&
            s[i + 2] == '=') {
            ++count;
            i += 2;
        } else if (i + 1 < s.size()) {
            if (s[i] == 'c' && s[i + 1] == '=') {
                ++count;
                ++i;
            } else if (s[i] == 'c' && s[i + 1] == '-') {
                ++count;
                ++i;
            } else if (s[i] == 'd' && s[i + 1] == '-') {
                ++count;
                ++i;
            } else if (s[i] == 'l' && s[i + 1] == 'j') {
                ++count;
                ++i;
            } else if (s[i] == 'n' && s[i + 1] == 'j') {
                ++count;
                ++i;
            } else if (s[i] == 's' && s[i + 1] == 'z') {
                ++count;
                ++i;
            } else if (s[i] == 's' && s[i + 1] == '=') {
                ++count;
                ++i;
            } else if (s[i] == 'z' && s[i + 1] == '=') {
                ++count;
                ++i;
            } else {
                ++count;
            }
        } else {
            ++count;
        }
    }

    std::cout << count << '\n';

    return 0;
}
