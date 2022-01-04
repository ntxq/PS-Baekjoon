#include <iostream>
#include <vector>

void preorder(const std::vector<std::vector<int>>& tree, int root) {
    if (root == -1) return;

    std::cout << static_cast<char>('A' + root);
    preorder(tree, tree[root][0]);
    preorder(tree, tree[root][1]);
}

void inorder(const std::vector<std::vector<int>>& tree, int root) {
    if (root == -1) return;

    inorder(tree, tree[root][0]);
    std::cout << static_cast<char>('A' + root);
    inorder(tree, tree[root][1]);
}

void postorder(const std::vector<std::vector<int>>& tree, int root) {
    if (root == -1) return;

    postorder(tree, tree[root][0]);
    postorder(tree, tree[root][1]);
    std::cout << static_cast<char>('A' + root);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> tree(n, std::vector<int>(2, -1));
    for (int i = 0; i < n; ++i) {
        char a, b, c;
        std::cin >> a >> b >> c;

        if (b != '.') tree[a - 'A'][0] = (b - 'A');
        if (c != '.') tree[a - 'A'][1] = (c - 'A');
    }

    preorder(tree, 0);
    std::cout << '\n';
    inorder(tree, 0);
    std::cout << '\n';
    postorder(tree, 0);

    return 0;
}