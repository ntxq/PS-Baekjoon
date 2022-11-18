#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

bool checkOp(int x, int y, char op) {
    switch (op) {
        case '<':
            return x < y;
        case '>':
            return x > y;
        default:
            return false;
    }
}

std::string backtrack(const std::string& ops, std::vector<bool>& visited,
                      std::string& num) {
    if (num.size() == ops.size() + 1) return num;

    for (int i = 0; i < 10; ++i)
        if (!visited[i] && checkOp(num.back() - '0', i, ops[num.size() - 1])) {
            visited[i] = true;
            num.push_back(i + '0');
            auto res = backtrack(ops, visited, num);
            if (!res.empty()) return res;
            num.pop_back();
            visited[i] = false;
        }

    return "";
}

std::string backtrackRev(const std::string& ops, std::vector<bool>& visited,
                         std::string& num) {
    if (num.size() == ops.size() + 1) return num;

    for (int i = 9; i >= 0; --i)
        if (!visited[i] && checkOp(num.back() - '0', i, ops[num.size() - 1])) {
            visited[i] = true;
            num.push_back(i + '0');
            auto res = backtrackRev(ops, visited, num);
            if (!res.empty()) return res;
            num.pop_back();
            visited[i] = false;
        }

    return "";
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int k;
    std::cin >> k;

    std::string ops(k, ' ');
    for (auto& op : ops) std::cin >> op;

    std::vector<bool> visited(10, false);
    std::string first = "", last = "";

    for (int i = 0; i < 10 && first.empty(); ++i) {
        visited[i] = true;
        first.push_back(i + '0');
        first = backtrack(ops, visited, first);
        visited[i] = false;
    }

    visited.assign(10, false);
    for (int i = 9; i >= 0 && last.empty(); --i) {
        visited[i] = true;
        last.push_back(i + '0');
        last = backtrackRev(ops, visited, last);
        visited[i] = false;
    }

    std::cout << last << '\n' << first << '\n';

    return 0;
}