#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> cards(N);
    for (int& card : cards) std::cin >> card;
    std::sort(cards.begin(), cards.end());

    int M;
    std::cin >> M;

    std::vector<int> queries(M);
    for (int& query : queries) std::cin >> query;

    std::transform(
        queries.begin(), queries.end(), queries.begin(), [&](int query) {
            return std::binary_search(cards.begin(), cards.end(), query);
        });

    for (int query : queries) std::cout << query << ' ';

    return 0;
}