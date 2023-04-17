#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::unordered_map<std::string, int> words;

    for (int i = 0; i < N; ++i) {
        std::string s;
        std::cin >> s;

        if (s.size() >= static_cast<unsigned>(M)) ++words[s];
    }

    std::vector<std::string> note;
    for (const auto& [word, _] : words) note.push_back(word);

    std::sort(note.begin(), note.end(),
              [&](const std::string& a, const std::string& b) {
                  if (words[a] != words[b]) return words[a] > words[b];
                  if (a.size() != b.size()) return a.size() > b.size();
                  return a < b;
              });

    for (const auto& word : note) std::cout << word << '\n';

    return 0;
}
