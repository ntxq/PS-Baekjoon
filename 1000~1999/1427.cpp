#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<int> N;
    
    char c;
    while (std::cin >> c)
        N.push_back(c - '0');
    
    std::sort(N.begin(), N.end(), std::greater<int>{});
    for (int i : N)
        std::cout << i;

    return 0;
}
