#include <iostream>
#include <string>

int main() {
    std::string str;
    std::cin >> str;

    int alpha[26]{};
    for (const char& c : str)
        if (c >= 'a' && c <= 'z')
            ++alpha[c - 'a'];
        else if (c >= 'A' && c <= 'Z')
            ++alpha[c - 'A'];

    int max_cnt = -1;
    int max_idx = -1;
    for (int i = 0; i < 26; ++i)
        if (alpha[i] > max_cnt) {
            max_cnt = alpha[i];
            max_idx = i;
        } else if (alpha[i] == max_cnt) {
            max_idx = -1;
        }

    std::cout << (max_idx == -1 ? '?' : static_cast<char>('A' + max_idx));

    return 0;
}