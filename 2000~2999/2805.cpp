#include <iostream>
#include <queue>
#include <utility>
#include <vector>

unsigned long long possibleCut(unsigned long long cut,
                               const std::vector<unsigned long long>& trees) {
    unsigned long long result = 0;
    for (const auto& tree : trees)
        if (tree > cut) result += tree - cut;

    return result;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned long long n, m;
    std::cin >> n >> m;

    std::vector<unsigned long long> trees(n);

    unsigned long long low = 0, high = 0;
    for (unsigned long long& tree : trees) {
        std::cin >> tree;

        if (tree > high) high = tree;
    }

    while (low <= high) {
        if (possibleCut((low + high) / 2, trees) < m)
            high = (low + high) / 2 - 1;
        else
            low = (low + high) / 2 + 1;
    }

    std::cout << high;

    return 0;
}