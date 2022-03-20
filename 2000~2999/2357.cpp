#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

void build(int v, int tl, int tr, const std::vector<int>& a,
           std::vector<std::pair<int, int>>& t) {
    if (tl == tr) {
        t[v] = {a[tl], a[tr]};
        return;
    }

    int tm = (tl + tr) / 2;
    build(v * 2 + 1, tl, tm, a, t);
    build(v * 2 + 2, tm + 1, tr, a, t);
    t[v] = {std::min(t[v * 2 + 1].first, t[v * 2 + 2].first),
            std::max(t[v * 2 + 1].second, t[v * 2 + 2].second)};
}

std::pair<int, int> rangeMinMax(int v, int tl, int tr, int l, int r,
                                const std::vector<std::pair<int, int>>& t) {
    if (l > r) return {1000000000, 0};
    if (l == tl && r == tr) return t[v];

    int tm = (tl + tr) / 2;

    std::pair<int, int> left =
        rangeMinMax(v * 2 + 1, tl, tm, l, std::min(r, tm), t);
    std::pair<int, int> right =
        rangeMinMax(v * 2 + 2, tm + 1, tr, std::max(l, tm + 1), r, t);

    return {std::min(left.first, right.first),
            std::max(left.second, right.second)};
}

void update(int v, int tl, int tr, int pos, int new_val,
            std::vector<std::pair<int, int>>& t) {
    if (tl == tr) {
        t[v] = {new_val, new_val};
        return;
    }

    int tm = (tl + tr) / 2;
    if (pos <= tm)
        update(v * 2 + 1, tl, tm, pos, new_val, t);
    else
        update(v * 2 + 2, tm + 1, tr, pos, new_val, t);

    t[v] = {std::min(t[v * 2 + 1].first, t[v * 2 + 2].first),
            std::max(t[v * 2 + 1].second, t[v * 2 + 2].second)};
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (auto& i : a) std::cin >> i;

    std::vector<std::pair<int, int>> t(4 * n);
    build(0, 0, n - 1, a, t);

    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;

        std::pair<int, int> minMax = rangeMinMax(0, 0, n - 1, a - 1, b - 1, t);
        std::cout << minMax.first << ' ' << minMax.second << '\n';
    }

    return 0;
}
