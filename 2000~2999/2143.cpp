#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    long long t;
    std::cin >> t;

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int& i : a) std::cin >> i;

    int m;
    std::cin >> m;
    std::vector<int> b(m);
    for (int& i : b) std::cin >> i;

    std::map<long long, long long> sums;
    for (int i = 0; i < n; ++i) {
        int curSum = 0;
        for (int j = i; j < n; ++j) {
            curSum += a[j];
            ++sums[curSum];
        }
    }

    unsigned long long count = 0;
    for (int i = 0; i < m; ++i) {
        int curSum = 0;
        for (int j = i; j < m; ++j) {
            curSum += b[j];
            if (auto it = sums.find(t - curSum); it != sums.end())
                count += it->second;
        }
    }

    std::cout << count << '\n';

    return 0;
}
