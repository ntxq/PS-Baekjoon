#include <algorithm>
#include <iostream>
#include <vector>

int N, M, K;
std::vector<unsigned long long> t;

void build(const std::vector<unsigned long long>& input, int v, int tl,
           int tr) {
    if (tl == tr) {
        t[v] = input[tl] % 1000000007;
    } else {
        int tm = (tl + tr) / 2;
        build(input, v * 2, tl, tm);
        build(input, v * 2 + 1, tm + 1, tr);
        t[v] = (t[v * 2] * t[v * 2 + 1]) % 1000000007;
    }
}

void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v * 2, tl, tm, pos, new_val);
        else
            update(v * 2 + 1, tm + 1, tr, pos, new_val);
        t[v] = (t[v * 2] * t[v * 2 + 1]) % 1000000007;
    }
}

unsigned long long product(int v, int tl, int tr, int l, int r) {
    if (l > r) return 1;
    if (l == tl && r == tr) return t[v];

    int tm = (tl + tr) / 2;
    return (product(v * 2, tl, tm, l, std::min(r, tm)) *
            product(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r)) %
           1000000007;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::cin >> N >> M >> K;

    std::vector<unsigned long long> input(N);
    for (auto& i : input) std::cin >> i;

    t.resize(2 * N);
    build(input, 1, 0, N - 1);

    for (int i = 0; i < M + K; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;

        if (a == 1)
            update(1, 0, N - 1, b - 1, c);
        else
            std::cout << product(1, 0, N - 1, b - 1, c - 1) << '\n';
    }

    return 0;
}