#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned l;
    std::cin >> l;

    std::string s;
    std::cin >> s;

    unsigned long long cnt = 0;
    for (unsigned i = s.size() - 1; i < s.size(); --i) {
        cnt *= 31;
        cnt += s[i] - 'a' + 1;
        cnt %= 1234567891;
    }

    std::cout << cnt;

    return 0;
}