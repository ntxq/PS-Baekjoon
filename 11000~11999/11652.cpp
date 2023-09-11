#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::unordered_map<long long, int> cards;
    for (int i = 0; i < N; ++i) {
        long long card;
        std::cin >> card;

        ++cards[card];
    }

    std::cout << std::max_element(cards.cbegin(), cards.cend(),
                                  [](const auto& lhs, const auto& rhs) {
                                      if (lhs.second == rhs.second)
                                          return lhs.first > rhs.first;
                                      return lhs.second < rhs.second;
                                  })
                     ->first
              << '\n';

    return 0;
}
