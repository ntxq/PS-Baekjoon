#include <bitset>
#include <iostream>
#include <map>
#include <string>

class AlgoSet {
   public:
    void add() {
        int x;
        std::cin >> x;
        s[x] = true;
    }

    void remove() {
        int x;
        std::cin >> x;
        s[x] = false;
    }

    void check() {
        int x;
        std::cin >> x;
        std::cout << s[x] << '\n';
    }

    void toggle() {
        int x;
        std::cin >> x;
        s.flip(x);
    }

    void all() { s.set(); }

    void empty() { s.reset(); }

   private:
    std::bitset<21> s;
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int size;
    std::cin >> size;

    std::map<std::string, void (AlgoSet::*)()> m;
    m["add"] = &AlgoSet::add;
    m["remove"] = &AlgoSet::remove;
    m["check"] = &AlgoSet::check;
    m["toggle"] = &AlgoSet::toggle;
    m["all"] = &AlgoSet::all;
    m["empty"] = &AlgoSet::empty;

    AlgoSet algo;
    for (std::string cmd; std::cin >> cmd;) (algo.*m[cmd])();

    return 0;
}