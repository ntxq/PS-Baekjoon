#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> A(n);
    for (int& i : A) std::cin >> i;

    int x;
    std::cin >> x;

    std::sort(A.begin(), A.end());

    auto low = A.begin();
    auto high = A.end() - 1;

    int count = 0;
    while (low < high) {
        int sum = *low + *high;
        if (sum == x) {
            ++count;
            ++low;
        } else if (sum < x) {
            ++low;
        } else {
            --high;
        }
    }

    std::cout << count << '\n';

    return 0;
}