#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

class Trie {
   public:
    Trie() : depth(0), children() {}
    Trie(int depth) : depth(depth), children() {}

    void insert(const std::string& s) {
        std::stringstream ss;
        std::string segment;

        ss << s;
        Trie* current = this;
        while (std::getline(ss, segment, '\\') && !segment.empty())
            current = current->insert_segment(segment);
    }

    void traverse() const {
        for (const auto& [key, value] : children) {
            std::cout << std::string(depth, ' ') << key << '\n';
            value.traverse();
        }
    }

   private:
    int depth;
    std::map<std::string, Trie> children;

    Trie* insert_segment(const std::string& s) {
        if (children.find(s) == children.end()) children[s] = Trie(depth + 1);

        return &children[s];
    }
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    Trie root;
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        root.insert(s);
    }

    root.traverse();

    return 0;
}
