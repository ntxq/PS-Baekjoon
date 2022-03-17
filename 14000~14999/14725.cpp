#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <string>

struct TreeNode {
    std::string val;
    std::map<std::string, TreeNode*> children;
};

void printTree(TreeNode* root, int level) {
    if (!root) return;

    for (int i = 0; i < level; ++i) std::cout << "--";
    std::cout << root->val << '\n';

    for (auto child : root->children) printTree(child.second, level + 1);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::map<std::string, TreeNode*> roots;
    for (int i = 0; i < n; ++i) {
        int k;
        std::cin >> k;

        std::map<std::string, TreeNode*>* curRoot = &roots;
        for (int j = 0; j < k; ++j) {
            std::string s;
            std::cin >> s;

            if (curRoot->find(s) == curRoot->end())
                curRoot->insert({s, new TreeNode{s, {}}});

            curRoot = &curRoot->at(s)->children;
        }
    }

    for (auto root : roots) printTree(root.second, 0);

    return 0;
}
