#include <algorithm>
#include <iostream>
#include <vector>

void build(int v, int tl, int tr, const std::vector<long long>& a,
           std::vector<long long>& t) {
    if (tl == tr) {
        t[v] = a[tl];
        return;
    }

    int tm = (tl + tr) / 2;
    build(v * 2 + 1, tl, tm, a, t);
    build(v * 2 + 2, tm + 1, tr, a, t);
    t[v] = t[v * 2 + 1] + t[v * 2 + 2];
}

long long sum(int v, int tl, int tr, int l, int r,
              const std::vector<long long>& t) {
    if (l > r) return 0;
    if (l == tl && r == tr) return t[v];

    int tm = (tl + tr) / 2;
    return sum(v * 2 + 1, tl, tm, l, std::min(r, tm), t) +
           sum(v * 2 + 2, tm + 1, tr, std::max(l, tm + 1), r, t);
}

void update(int v, int tl, int tr, int pos, long long new_val,
            std::vector<long long>& t) {
    if (tl == tr) {
        t[v] = new_val;
        return;
    }

    int tm = (tl + tr) / 2;
    if (pos <= tm)
        update(v * 2 + 1, tl, tm, pos, new_val, t);
    else
        update(v * 2 + 2, tm + 1, tr, pos, new_val, t);

    t[v] = t[v * 2 + 1] + t[v * 2 + 2];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<long long> a(n);
    for (auto& i : a) std::cin >> i;

    std::vector<long long> t(2 * n + 2);
    build(0, 0, n - 1, a, t);

    for (int i = 0; i < m + k; ++i) {
        long long x, y, z;
        std::cin >> x >> y >> z;

        if (x == 1)
            update(0, 0, n - 1, y - 1, z, t);
        else
            std::cout << sum(0, 0, n - 1, y - 1, z - 1, t) << '\n';
    }

    return 0;
}
