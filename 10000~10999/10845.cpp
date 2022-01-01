#include <iostream>
#include <map>
#include <queue>
#include <string>

class AlgoQueue {
   public:
    void push() {
        int x;
        std::cin >> x;
        q.push(x);
    }

    void pop() {
        if (q.empty()) {
            std::cout << -1 << '\n';
            return;
        }

        std::cout << q.front() << '\n';
        q.pop();
    }

    void size() { std::cout << q.size() << '\n'; }

    void empty() { std::cout << q.empty() << '\n'; }

    void front() {
        if (q.empty()) {
            std::cout << -1 << '\n';
            return;
        }

        std::cout << q.front() << '\n';
    }

    void back() {
        if (q.empty()) {
            std::cout << -1 << '\n';
            return;
        }

        std::cout << q.back() << '\n';
    }

   private:
    std::queue<int> q;
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int size;
    std::cin >> size;

    std::map<std::string, void (AlgoQueue::*)()> m;
    m["push"] = &AlgoQueue::push;
    m["pop"] = &AlgoQueue::pop;
    m["size"] = &AlgoQueue::size;
    m["empty"] = &AlgoQueue::empty;
    m["front"] = &AlgoQueue::front;
    m["back"] = &AlgoQueue::back;

    AlgoQueue q;
    for (std::string cmd; std::cin >> cmd;) (q.*m[cmd])();

    return 0;
}