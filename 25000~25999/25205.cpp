#include <algorithm>
#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    const char last[] = "rsefaqtdwczxvg";

    int N;
    std::cin >> N;

    std::string S;
    std::cin >> S;

    bool hasLast = false;
    for (int i = 0; last[i] && !hasLast; ++i)
        hasLast = S.back() == last[i];

    std::cout << hasLast << '\n';

    return 0;
}