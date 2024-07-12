#include <algorithm>
#include <bitset>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <ranges>
#include <vector>

class Trie {
   public:
    Trie() : is_end(false), children{} {}

    void insert(const std::ranges::input_range auto&& str) {
        Trie* node = this;
        for (const char& c : str) {
            if (node->children[c] == nullptr) node->children[c] = new Trie();

            node = node->children[c];
        }
        node->is_end = true;
    }

    std::bitset<2001> query(const std::ranges::input_range auto&& str) const {
        std::bitset<2001> lens;

        int curLen = 0;
        const Trie* node = this;
        for (const char& c : str) {
            if (!node->children.contains(c)) break;

            node = node->children.at(c);
            ++curLen;

            if (node->is_end) lens.set(curLen);
        }

        return lens;
    }

   private:
    bool is_end;
    std::map<char, Trie*> children;
};

bool check_legend(const Trie& colors, const Trie& names,
                  const std::string_view& team) {
    auto colorLens = colors.query(std::views::all(team));
    auto nameLens = names.query(std::views::reverse(team));

    int teamLen = team.size();
    for (int i = 1; i < teamLen; ++i)
        if (colorLens[i] && nameLens[teamLen - i]) return true;

    return false;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int c, n;
    std::cin >> c >> n;

    Trie colors;
    for (int i = 0; i < c; ++i) {
        std::string color;
        std::cin >> color;
        colors.insert(std::views::all(color));
    }

    Trie names;
    for (int i = 0; i < n; ++i) {
        std::string name;
        std::cin >> name;
        names.insert(std::views::reverse(name));
    }

    int q;
    std::cin >> q;

    for (int i = 0; i < q; ++i) {
        std::string team;
        std::cin >> team;
        std::cout << (check_legend(colors, names, team) ? "Yes" : "No") << '\n';
    }

    return 0;
}
