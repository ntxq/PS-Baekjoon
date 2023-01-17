#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

long long calculcate(long long a, char op, long long b) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        default:
            return 0;
    }
}

long long backtrack(std::size_t idx, const std::string& equation,
                    long long result) {
    if (idx >= equation.size()) return result;

    long long curResult = std::numeric_limits<long long>::min();
    if (idx + 2 < equation.size())
        curResult = backtrack(
            idx + 4, equation,
            calculcate(result, equation[idx - 1],
                       calculcate(equation[idx] - '0', equation[idx + 1],
                                  equation[idx + 2] - '0')));

    return std::max(curResult, backtrack(idx + 2, equation,
                                         calculcate(result, equation[idx - 1],
                                                    equation[idx] - '0')));
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::string equation;
    std::cin >> equation;

    if (N == 1)
        std::cout << equation << '\n';
    else
        std::cout << backtrack(2, equation, equation[0] - '0') << '\n';

    return 0;
}