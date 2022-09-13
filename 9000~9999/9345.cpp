#include <iostream>
#include <limits>
#include <vector>

struct Node {
    int min;
    int max;
};

std::vector<Node> segmentTree;

void build(int v, int tl, int tr) {
    if (tl == tr) {
        segmentTree[v] = {tl, tl};
    } else {
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm);
        build(v * 2 + 1, tm + 1, tr);
        segmentTree[v] = {
            std::min(segmentTree[v * 2].min, segmentTree[v * 2 + 1].min),
            std::max(segmentTree[v * 2].max, segmentTree[v * 2 + 1].max)};
    }
}

Node query(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return {std::numeric_limits<int>::max(),
                std::numeric_limits<int>::min()};
    if (l == tl && r == tr) return segmentTree[v];

    int tm = (tl + tr) / 2;
    auto left = query(v * 2, tl, tm, l, std::min(r, tm));
    auto right = query(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r);

    return {std::min(left.min, right.min), std::max(left.max, right.max)};
};

void update(int v, int tl, int tr, int pos, const Node& val) {
    if (tl == tr) {
        segmentTree[v] = val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v * 2, tl, tm, pos, val);
        else
            update(v * 2 + 1, tm + 1, tr, pos, val);
        segmentTree[v] = {
            std::min(segmentTree[v * 2].min, segmentTree[v * 2 + 1].min),
            std::max(segmentTree[v * 2].max, segmentTree[v * 2 + 1].max)};
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;

    std::cin >> T;
    while (T--) {
        int N, K;
        std::cin >> N >> K;

        segmentTree.assign(4 * N, {std::numeric_limits<int>::max(),
                                   std::numeric_limits<int>::min()});
        build(1, 0, N - 1);

        for (int i = 0; i < K; ++i) {
            int Q, A, B;
            std::cin >> Q >> A >> B;

            if (!Q) {
                Node a = query(1, 0, N - 1, A, A);
                Node b = query(1, 0, N - 1, B, B);
                update(1, 0, N - 1, A, b);
                update(1, 0, N - 1, B, a);
            } else {
                Node res = query(1, 0, N - 1, A, B);
                std::cout << (res.min == A && res.max == B ? "YES" : "NO")
                          << '\n';
            }
        }
    }

    return 0;
}