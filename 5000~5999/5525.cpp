#include <algorithm>
#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::string s;
    std::cin >> s;

    int curBeg = 0, curEnd = 1;
    bool isInitialI = s[0] == 'I';
    int curP = 0;

    int count = 0;
    while (curEnd < m) {
        if (isInitialI) {
            if (curEnd + 1 < m && s[curEnd] == 'O' && s[curEnd + 1] == 'I') {
                ++curP;
                curEnd += 2;
            } else {
                curBeg = curEnd;
                ++curEnd;
                isInitialI = s[curBeg] == 'I';
                curP = 0;
            }

            if (curP == n) {
                ++count;
                curBeg += 2;
                --curP;
            }
        } else {
            curBeg = curEnd;
            ++curEnd;
            isInitialI = s[curBeg] == 'I';
            curP = 0;
        }
    }

    std::cout << count;

    return 0;
}