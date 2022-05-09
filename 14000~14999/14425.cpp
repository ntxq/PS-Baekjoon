#include <algorithm>
#include <iostream>
#include <set>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::set<std::string> words;
    for (int i = 0; i < N; ++i) {
        std::string s;
        std::cin >> s;

        words.insert(s);
    }

    int count = 0;
    for (int i = 0; i < M; ++i) {
        std::string s;
        std::cin >> s;

        count += words.contains(s);
    }

    std::cout << count << '\n';

    return 0;
}