#include <iostream>
#include <vector>

std::vector<long long> T;

void build(const std::vector<int>& A, int v, int tl, int tr) {
    if (tl == tr) {
        T[v] = A[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(A, v * 2, tl, tm);
        build(A, v * 2 + 1, tm + 1, tr);
    }
}

void update(int v, int tl, int tr, int l, int r, int val) {
    if (l > r) return;

    if (l == tl && r == tr) {
        T[v] += val;
        return;
    }

    int tm = (tl + tr) / 2;
    update(v * 2, tl, tm, l, std::min(r, tm), val);
    update(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, val);
}

long long query(int v, int tl, int tr, int l, int r) {
    if (l > r) return 0;

    if (l == tl && r == tr) return T[v];

    int tm = (tl + tr) / 2;
    return T[v] + query(v * 2, tl, tm, l, std::min(r, tm)) +
           query(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> A(N);
    for (auto& i : A) std::cin >> i;

    T.assign(4 * N, 0);
    build(A, 1, 0, N - 1);

    int M;
    std::cin >> M;

    for (int i = 0; i < M; ++i) {
        int type;
        std::cin >> type;

        if (type == 1) {
            int I, J, K;
            std::cin >> I >> J >> K;

            update(1, 0, N - 1, I - 1, J - 1, K);
        } else {
            int X;
            std::cin >> X;

            std::cout << query(1, 0, N - 1, X - 1, X - 1) << '\n';
        }
    }

    return 0;
}