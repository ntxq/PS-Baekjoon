#include <iostream>
#include <map>
#include <stack>
#include <string>

class AlgoStack {
   public:
    void push() {
        int x;
        std::cin >> x;
        s.push(x);
    }

    void pop() {
        if (s.empty()) {
            std::cout << -1 << '\n';
            return;
        }

        std::cout << s.top() << '\n';
        s.pop();
    }

    void size() { std::cout << s.size() << '\n'; }

    void empty() { std::cout << s.empty() << '\n'; }

    void top() {
        if (s.empty()) {
            std::cout << -1 << '\n';
            return;
        }

        std::cout << s.top() << '\n';
    }

   private:
    std::stack<int> s;
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int size;
    std::cin >> size;

    std::map<std::string, void (AlgoStack::*)()> m;
    m["push"] = &AlgoStack::push;
    m["pop"] = &AlgoStack::pop;
    m["size"] = &AlgoStack::size;
    m["empty"] = &AlgoStack::empty;
    m["top"] = &AlgoStack::top;

    AlgoStack s;
    for (std::string cmd; std::cin >> cmd;) (s.*m[cmd])();

    return 0;
}