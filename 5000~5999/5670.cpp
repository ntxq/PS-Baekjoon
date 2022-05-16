#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Trie {
   public:
    Trie(bool isRoot) : isRoot(isRoot), isEnd(false), childCount(0){};

    void insert(const char* word) {
        if (!*word) {
            isEnd = true;
            return;
        }

        int pos = *word - 'a';
        if (!children[pos]) {
            children[pos] = std::make_unique<Trie>(false);
            ++childCount;
        }

        children[pos]->insert(word + 1);
    }

    int find(const char* word) {
        if (!*word) return 0;

        int pos = *word - 'a';
        if (isRoot || isEnd || childCount > 1)
            return 1 + children[pos]->find(word + 1);

        return children[pos]->find(word + 1);
    }

   private:
    bool isRoot;
    bool isEnd;
    int childCount;
    std::unique_ptr<Trie> children[26];
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    while (std::cin >> N) {
        Trie root(true);
        std::vector<std::string> words(N);

        for (int i = 0; i < N; ++i) {
            std::cin >> words[i];
            root.insert(words[i].c_str());
        }

        int total = 0;
        for (int i = 0; i < N; ++i) total += root.find(words[i].c_str());

        std::cout << std::fixed << std::setprecision(2)
                  << total / static_cast<double>(N) << '\n';
    }

    return 0;
}