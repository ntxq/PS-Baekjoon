#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

class SegmentTree {
   private:
    int n;
    std::vector<int> t;
    static constexpr int MOD = 1e9 + 7;

    int sum(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (l == tl && r == tr) return t[v];

        int tm = (tl + tr) / 2;
        return (sum(v * 2, tl, tm, l, std::min(r, tm)) +
                sum(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r)) %
               MOD;
    }

    void add(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            t[v] = (t[v] + new_val) % MOD;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                add(v * 2, tl, tm, pos, new_val);
            else
                add(v * 2 + 1, tm + 1, tr, pos, new_val);
            t[v] = (t[v * 2] + t[v * 2 + 1]) % MOD;
        }
    }

   public:
    SegmentTree(int n) : n(n), t(4 * n) {}
    int sum(int l, int r) { return sum(1, 0, n - 1, l, r); }
    void add(int pos, int new_val) { add(1, 0, n - 1, pos, new_val); }
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> nums(N);
    for (int& num : nums) std::cin >> num;

    std::vector<SegmentTree> trees(11, SegmentTree(N + 1));
    for (const int& num : nums) {
        trees[0].add(num, 1);
        for (int i = 1; i < 11; ++i)
            trees[i].add(num, trees[i - 1].sum(0, num - 1));
    }

    std::cout << trees[10].sum(0, N) << '\n';

    return 0;
}
