#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> tree;

void insert(int v, int tl, int tr, int pos) {
    ++tree[v];
    if (tl != tr) {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            insert(v * 2, tl, tm, pos);
        else
            insert(v * 2 + 1, tm + 1, tr, pos);
    }
}

int kth(int v, int tl, int tr, int k) {
    --tree[v];
    if (tl == tr) return tl;

    int tm = (tl + tr) / 2;
    if (tree[v * 2] >= k)
        return kth(v * 2, tl, tm, k);
    else
        return kth(v * 2 + 1, tm + 1, tr, k - tree[v * 2]);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    tree.resize(2000001 * 4);
    for (int i = 0; i < N; ++i) {
        int T, X;
        std::cin >> T >> X;

        if (T == 1)
            insert(1, 0, 2000000, X);
        else
            std::cout << kth(1, 0, 2000000, X) << '\n';
    }

    return 0;
}