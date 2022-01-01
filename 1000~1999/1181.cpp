#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);

    int size;
    std::cin >> size;

    std::vector<std::string> words;
    for (int i = 0; i < size; i++) {
        std::string word;
        std::cin >> word;
        words.push_back(word);
    }

    std::sort(words.begin(), words.end(),
              [](const std::string& a, const std::string& b) {
                  return a.size() != b.size() ? a.size() < b.size() : a < b;
              });
    auto end = std::unique(words.begin(), words.end());

    for (auto it = words.begin(); it != end; ++it) std::cout << *it << '\n';

    return 0;
}