
#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <set>
#include <string>
#include <vector>

bool is_word(const std::string& word, std::multiset<std::string>& word_set) {
    std::string prefix = "";
    for (int i = 0; i < word.size() - 1; ++i) {
        prefix += word[i];

        auto found = word_set.find(prefix);
        if (found == word_set.end()) return false;
        word_set.erase(found);
    }

    std::string suffix = "";
    for (int i = word.size() - 1; i > 0; --i) {
        suffix = word[i] + suffix;

        auto found = word_set.find(suffix);
        if (found == word_set.end()) return false;
        word_set.erase(found);
    }

    return true;
}

bool is_prefix(const std::string& candidate, const std::string& word) {
    return std::equal(candidate.begin(), candidate.end(), word.begin());
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::string> words(2 * N - 2);
    for (auto& word : words) std::cin >> word;

    std::string x, y;
    for (const auto& word : words)
        if (word.size() == N - 1) (x.empty() ? x : y) = word;

    std::string word1 = x + y.back();
    std::string word2 = y + x.back();

    std::multiset<std::string> word_set(words.begin(), words.end());
    const auto& word = (is_word(word1, word_set) ? word1 : word2);
    std::cout << word << '\n';

    std::vector<bool> counts(N - 1, true);
    for (const auto& candidate : words)
        if (counts[candidate.size() - 1] && is_prefix(candidate, word)) {
            std::cout << "P";
            counts[candidate.size() - 1] = false;
        } else {
            std::cout << "S";
        }
    std::cout << '\n';

    return 0;
}
