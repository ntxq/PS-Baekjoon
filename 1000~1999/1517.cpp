#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::pair<int, int>> A;
std::vector<unsigned long long> T;

void update(int v, int tl, int tr, int pos) {
    if (tl == tr) {
        T[v] = 1;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v * 2, tl, tm, pos);
        else
            update(v * 2 + 1, tm + 1, tr, pos);
        T[v] = T[v * 2] + T[v * 2 + 1];
    }
}

unsigned long long query(int v, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    if (l == tl && r == tr) return T[v];

    int tm = (tl + tr) / 2;
    return query(v * 2, tl, tm, l, std::min(r, tm)) +
           query(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::pair<int, int>*> B(N);
    A.resize(N);

    for (int i = 0; i < N; ++i) {
        std::cin >> A[i].first;
        B[i] = &A[i];
    }

    std::stable_sort(B.begin(), B.end(),
              [](auto a, auto b) { return a->first < b->first; });
    for (int i = 0; i < N; ++i) B[i]->second = i;

    T.assign(4 * N, 0);
    unsigned long long ans = 0;
    for (int i = 0; i < N; ++i) {
        ans += query(1, 0, N - 1, A[i].second + 1, N - 1);
        update(1, 0, N - 1, A[i].second);
    }

    std::cout << ans << '\n';

    return 0;
}