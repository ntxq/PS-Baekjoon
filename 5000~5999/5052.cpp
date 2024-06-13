#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

class Trie {
   public:
    bool is_end;
    Trie* children[10];

    Trie() : is_end(false), children{} {}

    ~Trie() {
        for (auto child : children)
            if (child) delete child;
    }

    Trie* insert(char digit) {
        if (!children[digit - '0']) children[digit - '0'] = new Trie();
        return children[digit - '0'];
    }
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<std::string> phone_numbers(n);
        for (auto& phone_number : phone_numbers) std::cin >> phone_number;
        std::sort(phone_numbers.begin(), phone_numbers.end(),
                  [](const std::string& a, const std::string& b) {
                      return a.size() < b.size();
                  });

        bool is_consistent = true;
        Trie root;

        for (int i = 0; i < n && is_consistent; ++i) {
            Trie* current = &root;
            for (int j = 0; j < phone_numbers[i].size() && is_consistent; ++j) {
                current = current->insert(phone_numbers[i][j]);
                if (current->is_end) is_consistent = false;
            }
            current->is_end = true;
        }

        std::cout << (is_consistent ? "YES" : "NO") << '\n';
    }

    return 0;
}
