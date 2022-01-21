#include <algorithm>
#include <iostream>
#include <vector>

void fillPre(std::vector<int>& pre, std::vector<int>& post,
             const std::vector<int>& in, int start, int end) {
    if (start > end) return;

    int root = post.back();
    post.pop_back();

    int rootIndex =
        std::find(in.begin() + start, in.begin() + end + 1, root) - in.begin();

    fillPre(pre, post, in, rootIndex + 1, end);
    fillPre(pre, post, in, start, rootIndex - 1);

    pre.push_back(root);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> in(n);
    for (int& i : in) std::cin >> i;

    std::vector<int> post(n);
    for (int& i : post) std::cin >> i;

    std::vector<int> pre;
    fillPre(pre, post, in, 0, n - 1);

    while (!pre.empty()) {
        std::cout << pre.back() << ' ';
        pre.pop_back();
    }

    return 0;
}