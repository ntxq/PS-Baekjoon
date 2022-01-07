#include <deque>
#include <iostream>
#include <stack>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::deque<int> seq(n);
    for (int i = 0; i < n; ++i) std::cin >> seq[i];

    std::stack<int> aux;
    std::string ans;

    int top = 0;
    bool isValid = true;
    while (!seq.empty() && isValid) {
        if (aux.empty() || aux.top() < seq.front()) {
            aux.push(++top);
            ans.append("+\n");
        } else if (aux.top() == seq.front()) {
            aux.pop();
            ans.append("-\n");
            seq.pop_front();
        } else {
            isValid = false;
            ans = "NO";
        }
    }

    std::cout << ans;

    return 0;
}