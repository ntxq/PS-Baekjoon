#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

std::vector<char> handle_line(std::vector<char>& stack, int repeat,
                              std::queue<char>& line) {
    char next = line.front();
    line.pop();

    switch (next) {
        case 'a' ... 'z':
            stack.push_back(next);
            return handle_line(stack, repeat, line);

        case '0' ... '9':
            repeat = repeat * 10 + (next - '0');
            return handle_line(stack, repeat, line);

        case ' ':
            return handle_line(stack, repeat, line);

        case '(': {
            std::vector<char> sub_stack;
            for (char c : handle_line(sub_stack, 0, line)) stack.push_back(c);
            return handle_line(stack, repeat, line);
        }

        case ')': {
            std::vector<char> repeated_stack;
            for (int i = 0; i < repeat; ++i)
                std::copy(stack.begin(), stack.end(),
                          std::back_inserter(repeated_stack));
            return repeated_stack;
        }

        case '$':
            return stack;
    }
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    std::string testcase;

    while (std::getline(std::cin, testcase) && testcase != "$") {
        std::vector<char> stack;
        std::queue<char> line;
        for (char c : testcase) line.push(c);

        for (char c : handle_line(stack, 0, line)) std::cout << c;
        std::cout << '\n';
    }

    return 0;
}