#include <iostream>
#include <stack>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    for (std::string line; std::getline(std::cin, line), line != ".";) {
        bool isBalanced = true;
        std::stack<char> s;

        for (unsigned i = 0; i < line.size() && isBalanced; ++i) {
            if (line[i] == '[') {
                s.push(line[i]);
            } else if (line[i] == ']') {
                if (s.empty() || s.top() != '[')
                    isBalanced = false;
                else
                    s.pop();
            } else if (line[i] == '(') {
                s.push(line[i]);
            } else if (line[i] == ')') {
                if (s.empty() || s.top() != '(')
                    isBalanced = false;
                else
                    s.pop();
            }
        }

        std::cout << (isBalanced && s.size() == 0 ? "yes\n" : "no\n");
    }

    return 0;
}