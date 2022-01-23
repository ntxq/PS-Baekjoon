#include <algorithm>
#include <iostream>
#include <vector>

void postorder(const std::vector<int>& tree, int l, int r) {
    if (l > r) return;

    int root = tree[l];
    int split = l + 1;
    while (split <= r && tree[split] < root) ++split;

    postorder(tree, l + 1, split - 1);
    postorder(tree, split, r);

    std::cout << root << '\n';
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<int> tree;

    int x;
    while (std::cin >> x) tree.push_back(x);

    postorder(tree, 0, tree.size() - 1);

    return 0;
}