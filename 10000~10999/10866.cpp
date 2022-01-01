#include <deque>
#include <iostream>
#include <map>
#include <string>

class AlgoDeque {
   public:
    void push_front() {
        int x;
        std::cin >> x;
        d.push_front(x);
    }

    void push_back() {
        int x;
        std::cin >> x;
        d.push_back(x);
    }

    void pop_front() {
        if (d.empty()) {
            std::cout << -1 << '\n';
            return;
        }

        std::cout << d.front() << '\n';
        d.pop_front();
    }

    void pop_back() {
        if (d.empty()) {
            std::cout << -1 << '\n';
            return;
        }

        std::cout << d.back() << '\n';
        d.pop_back();
    }

    void size() { std::cout << d.size() << '\n'; }

    void empty() { std::cout << d.empty() << '\n'; }

    void front() {
        if (d.empty()) {
            std::cout << -1 << '\n';
            return;
        }

        std::cout << d.front() << '\n';
    }

    void back() {
        if (d.empty()) {
            std::cout << -1 << '\n';
            return;
        }

        std::cout << d.back() << '\n';
    }

   private:
    std::deque<int> d;
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int size;
    std::cin >> size;

    std::map<std::string, void (AlgoDeque::*)()> m;
    m["push_front"] = &AlgoDeque::push_front;
    m["push_back"] = &AlgoDeque::push_back;
    m["pop_front"] = &AlgoDeque::pop_front;
    m["pop_back"] = &AlgoDeque::pop_back;
    m["size"] = &AlgoDeque::size;
    m["empty"] = &AlgoDeque::empty;
    m["front"] = &AlgoDeque::front;
    m["back"] = &AlgoDeque::back;

    AlgoDeque d;
    for (std::string cmd; std::cin >> cmd;) (d.*m[cmd])();

    return 0;
}