#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

std::vector<char> shuntingYard(const std::vector<char>& expression) {
    std::vector<char> output;
    std::vector<char> operators;

    for (std::size_t i = 0; i < expression.size(); ++i) {
        const char c = expression[i];

        if ('0' <= c && c <= '9') {
            output.push_back(c);
        } else if (c == '*') {
            while (!operators.empty() && operators.back() == '*') {
                output.push_back(operators.back());
                operators.pop_back();
            }
            operators.push_back(c);
        } else if (c == '+' || c == '-') {
            while (!operators.empty() && operators.back() != '(') {
                output.push_back(operators.back());
                operators.pop_back();
            }
            operators.push_back(c);
        } else if (c == '(') {
            operators.push_back(c);
        } else if (c == ')') {
            while (operators.back() != '(') {
                output.push_back(operators.back());
                operators.pop_back();
            }
            operators.pop_back();
        }
    }

    while (!operators.empty()) {
        output.push_back(operators.back());
        operators.pop_back();
    }

    return output;
}

int evaluate(const std::vector<char>& expression) {
    std::vector<int> stack;

    for (std::size_t i = 0; i < expression.size(); ++i) {
        const char c = expression[i];

        if ('0' <= c && c <= '9') {
            stack.push_back(c - '0');
        } else if (c == '*') {
            const int a = stack.back();
            stack.pop_back();
            const int b = stack.back();
            stack.pop_back();
            stack.push_back(a * b);
        } else if (c == '+') {
            const int a = stack.back();
            stack.pop_back();
            const int b = stack.back();
            stack.pop_back();
            stack.push_back(a + b);
        } else if (c == '-') {
            const int a = stack.back();
            stack.pop_back();
            const int b = stack.back();
            stack.pop_back();
            stack.push_back(b - a);
        }
    }

    return stack.back();
}

int backtrack(int idx, bool isOpened, std::vector<char>& transformed,
              const int N, const std::vector<char>& expression) {
    if (idx == N) {
        if (isOpened) transformed.push_back(')');
        int result = evaluate(shuntingYard(transformed));
        if (isOpened) transformed.pop_back();
        return result;
    }

    if (!isOpened) {
        transformed.push_back(expression[idx]);
        transformed.push_back(expression[idx + 1]);
        int result = backtrack(idx + 2, false, transformed, N, expression);
        transformed.pop_back();

        transformed.push_back('(');
        transformed.push_back(expression[idx + 1]);
        result = std::max(result,
                          backtrack(idx + 2, true, transformed, N, expression));
        transformed.pop_back();
        transformed.pop_back();
        transformed.pop_back();

        return result;
    } else {
        transformed.push_back(expression[idx]);
        transformed.push_back(expression[idx + 1]);
        transformed.push_back(')');
        int result = backtrack(idx + 2, false, transformed, N, expression);
        transformed.pop_back();
        transformed.pop_back();
        transformed.pop_back();

        return result;
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<char> expression(N);
    for (char& c : expression) std::cin >> c;


    std::vector<char> transformed{expression[0]};
    int result = backtrack(1, false, transformed, N, expression);

    transformed = {'(', expression[0]};
    result = std::max(result, backtrack(1, true, transformed, N, expression));

    std::cout << result << '\n';

    return 0;
}