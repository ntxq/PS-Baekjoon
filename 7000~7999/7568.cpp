#include <iostream>
#include <utility>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> people(n);

    for (int i = 0; i < n; ++i) std::cin >> people[i].first >> people[i].second;

    for (int i = 0; i < n; ++i) {
        int bigger = 0;

        for (int j = 0; j < n; ++j)
            if (people[i].first < people[j].first &&
                people[i].second < people[j].second)
                ++bigger;

        std::cout << bigger + 1 << ' ';
    }

    return 0;
}