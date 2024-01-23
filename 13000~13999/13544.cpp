#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

constexpr int MAXN = 100000;
std::vector<int> tree[4 * MAXN];

void build(const std::vector<int>& inputs, int v, int tl, int tr) {
    if (tl == tr)
        tree[v] = {inputs[tl]};
    else {
        int tm = (tl + tr) / 2;
        build(inputs, v * 2, tl, tm);
        build(inputs, v * 2 + 1, tm + 1, tr);
        std::merge(tree[v * 2].begin(), tree[v * 2].end(),
                   tree[v * 2 + 1].begin(), tree[v * 2 + 1].end(),
                   std::back_inserter(tree[v]));
    }
}

int query(int v, int tl, int tr, int l, int r, int x) {
    if (l > r) return 0;

    if (l == tl && r == tr)
        return tree[v].end() -
               std::upper_bound(tree[v].begin(), tree[v].end(), x);

    int tm = (tl + tr) / 2;
    return query(v * 2, tl, tm, l, std::min(r, tm), x) +
           query(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, x);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> inputs(N);
    for (int& i : inputs) std::cin >> i;
    build(inputs, 1, 0, N - 1);

    int M;
    std::cin >> M;

    int last_ans = 0;
    for (int i = 0; i < M; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        a ^= last_ans;
        b ^= last_ans;
        c ^= last_ans;

        last_ans = query(1, 0, N - 1, a - 1, b - 1, c);
        std::cout << last_ans << '\n';
    }

    return 0;
}
