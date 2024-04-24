#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

std::array<int, 10> is_num_used{};
std::array<int, 26> char_to_num{};

bool backtrack(std::vector<char>& chars, const std::string& a,
               const std::string& b, const std::string& c) {
    if (chars.empty()) {
        int aNum = 0, bNum = 0, cNum = 0;
        for (const char& ch : a) aNum = aNum * 10 + char_to_num[ch - 'A'];
        for (const char& ch : b) bNum = bNum * 10 + char_to_num[ch - 'A'];
        for (const char& ch : c) cNum = cNum * 10 + char_to_num[ch - 'A'];
        return aNum + bNum == cNum;
    }

    const char ch = chars.back();
    chars.pop_back();

    for (int i = 0; i < 10; ++i) {
        if (is_num_used[i]) continue;

        is_num_used[i] = true;
        char_to_num[ch - 'A'] = i;
        if (backtrack(chars, a, b, c)) return true;
        is_num_used[i] = false;
    }

    chars.push_back(ch);
    return false;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string a, b, c;
    std::cin >> a >> b >> c;

    std::array<bool, 26> is_char_used{};
    for (const char& ch : a) is_char_used[ch - 'A'] = true;
    for (const char& ch : b) is_char_used[ch - 'A'] = true;
    for (const char& ch : c) is_char_used[ch - 'A'] = true;

    std::vector<char> chars;
    for (int i = 0; i < 26; ++i)
        if (is_char_used[i]) chars.push_back('A' + i);

    if (backtrack(chars, a, b, c))
        std::cout << "YES\n";
    else
        std::cout << "NO\n";

    return 0;
}
