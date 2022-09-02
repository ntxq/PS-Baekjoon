#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, k;
    std::cin >> N >> k;

    std::vector<int> scores(N);
    for (int& i : scores) std::cin >> i;

    std::nth_element(scores.begin(), scores.end() - k, scores.end());
    std::cout << scores[scores.size() - k] << '\n';

    return 0;
}