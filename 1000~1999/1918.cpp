#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string tokens;
    std::cin >> tokens;

    std::vector<char> s;
    std::queue<char> q;

    for (const char& c : tokens) {
        if ('A' <= c && c <= 'Z') {
            q.push(c);
        } else if (c != '(' && c != ')') {
            while (!s.empty() && s.back() != '(' &&
                   !(((s.back() == '+' || s.back() == '-') &&
                      (c == '*' || c == '/')))) {
                q.push(s.back());
                s.pop_back();
            }
            s.push_back(c);
        } else if (c == '(') {
            s.push_back(c);
        } else if (c == ')') {
            while (s.back() != '(') {
                q.push(s.back());
                s.pop_back();
            }
            s.pop_back();
        }
    }

    while (!s.empty()) {
        q.push(s.back());
        s.pop_back();
    }

    while (!q.empty()) {
        std::cout << q.front();
        q.pop();
    }

    return 0;
}