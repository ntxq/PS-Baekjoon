#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int find(int x, std::vector<int>& parents) {
    int root = x;
    while (root != parents[root]) root = parents[root];

    while (x != parents[x]) {
        int next = parents[x];
        parents[x] = root;
        x = next;
    }

    return root;
}

void unite(int x, int y, std::vector<int>& parents) {
    int xroot = find(x, parents);
    int yroot = find(y, parents);

    parents[xroot] = yroot;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int g, p;
    std::cin >> g >> p;

    std::vector<int> parents(g + 1);

    std::iota(parents.begin(), parents.end(), 0);

    int count = 0;
    bool isFull = false;

    while (count < p && !isFull) {
        int target;
        std::cin >> target;

        if (!find(target, parents))
            isFull = true;
        else
            unite(parents[target], parents[target] - 1, parents);

        ++count;
    }

    std::cout << count - isFull << '\n';

    return 0;
}
