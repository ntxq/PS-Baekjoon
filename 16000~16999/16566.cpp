#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int find(int x, std::vector<int>& parents) {
    if (parents[x] == x) return x;

    return parents[x] = find(parents[x], parents);
}

void unite(int x, int y, std::vector<int>& parents) {
    int xroot = find(x, parents);
    int yroot = find(y, parents);

    parents[xroot] = yroot;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<int> selected;
    for (int i = 0; i < m; ++i) {
        int x;
        std::cin >> x;

        selected.push_back(x);
    }

    std::sort(selected.begin(), selected.end());

    std::vector<int> parents(m);
    std::iota(parents.begin(), parents.end(), 0);

    for (int i = 0; i < k; ++i) {
        int x;
        std::cin >> x;

        int next = find(std::upper_bound(selected.begin(), selected.end(), x) -
                            selected.begin(),
                        parents);
        std::cout << selected[next] << '\n';

        if (next < m - 1)
            unite(next, next + 1, parents);
    }

    return 0;
}
