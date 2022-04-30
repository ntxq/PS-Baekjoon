#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

std::string find(std::string x, std::map<std::string, std::string>& parents) {
    std::string root = parents[x];
    while (root != parents[root]) root = parents[root];

    while (x != parents[x]) {
        std::string next = parents[x];
        parents[x] = root;
        x = next;
    }

    return root;
}

void unite(std::string x, std::string y,
           std::map<std::string, std::string>& parents,
           std::map<std::string, int>& sizes) {
    std::string xroot = find(x, parents);
    std::string yroot = find(y, parents);

    if (xroot != yroot) {
        if (sizes[xroot] < sizes[yroot]) {
            parents[xroot] = yroot;
            sizes[yroot] += sizes[xroot];
        } else {
            parents[yroot] = xroot;
            sizes[xroot] += sizes[yroot];
        }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int t = 0; t < T; ++t) {
        int F;
        std::cin >> F;

        std::map<std::string, std::string> parents;
        std::map<std::string, int> sizes;

        for (int i = 0; i < F; ++i) {
            std::string a, b;
            std::cin >> a >> b;

            if (!parents.contains(a)) {
                parents[a] = a;
                sizes[a] = 1;
            }
            if (!parents.contains(b)) {
                parents[b] = b;
                sizes[b] = 1;
            }

            unite(a, b, parents, sizes);
            std::cout << sizes[find(a, parents)] << '\n';
        }
    }

    return 0;
}