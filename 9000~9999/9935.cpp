#include <iostream>
#include <stack>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string seq;
    std::cin >> seq;

    std::string bomb;
    std::cin >> bomb;

    std::stack<int> s;
    std::string ans;

    int maxLength = bomb.length();
    for (const char& c : seq) {
        if (s.empty()) {
            s.push(c == bomb[0]);
            ans.push_back(c);
        } else {
            int prev = s.top();
            int cur = c == bomb[prev] ? prev + 1 : c == bomb[0];

            s.push(cur);
            ans.push_back(c);
        }

        if (s.top() == maxLength)
            for (int i = 0; i < maxLength; ++i) {
                s.pop();
                ans.pop_back();
            }
    }

    std::cout << (ans.empty() ? "FRULA" : ans);

    return 0;
}