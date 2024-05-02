#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int N;
        std::cin >> N;

        std::vector<int> nums(N);
        std::iota(nums.begin(), nums.end(), 1);

        std::vector<int> r(N);
        for (int& i : r) std::cin >> i;

        std::vector<int> s;

        bool is_possible = true;
        for (int i = N - 1; i >= 0 && is_possible; --i) {
            int idx = r[i];
            if (idx >= nums.size()) {
                is_possible = false;
                break;
            }

            s.push_back(nums[idx]);
            nums.erase(nums.begin() + idx);
        }

        if (!is_possible) {
            std::cout << "IMPOSSIBLE\n";
        } else {
            for (int i = N - 1; i >= 0; --i) std::cout << s[i] << ' ';
            std::cout << '\n';
        }
    }

    return 0;
}
