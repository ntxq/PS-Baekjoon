#include <algorithm>
#include <iostream>
#include <numeric>

std::vector<int> parents;
std::vector<int> ranks;
std::vector<int> ancestor;

int find_set(int x) {
    int root = x;
    while (parents[root] != root) root = parents[root];

    while (parents[x] != root) {
        int next = parents[x];
        parents[x] = root;
        x = next;
    }

    return root;
}

void union_set(int x, int y) {
    int xroot = find_set(x);
    int yroot = find_set(y);

    if (xroot != yroot) {
        if (ranks[xroot] < ranks[yroot]) {
            parents[xroot] = yroot;
        } else if (ranks[xroot] > ranks[yroot]) {
            parents[yroot] = xroot;
        } else {
            parents[yroot] = xroot;
            ranks[xroot]++;
        }
    }
}

void lca(int u, int x, int y, const std::vector<std::vector<int>>& adj,
         bool& isAnswered) {
    ancestor[u] = u;
    for (int v : adj[u])
        if (!ancestor[v]) {
            lca(v, x, y, adj, isAnswered);
            union_set(u, v);
            ancestor[find_set(u)] = u;
        }

    if (u == x && ancestor[find_set(y)] && !isAnswered) {
        std::cout << ancestor[find_set(y)] << '\n';
        isAnswered = true;
    } else if (u == y && ancestor[find_set(x)] && !isAnswered) {
        std::cout << ancestor[find_set(x)] << '\n';
        isAnswered = true;
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int N;
        std::cin >> N;

        std::vector<std::vector<int>> adj(N + 1);
        std::vector<int> adjRev(N + 1);
        for (int i = 1; i < N; ++i) {
            int u, v;
            std::cin >> u >> v;

            adj[u].push_back(v);
            adjRev[v] = u;
        }

        int x, y;
        std::cin >> x >> y;

        int root = x;
        while (adjRev[root]) root = adjRev[root];

        parents.resize(N + 1);
        ranks.resize(N + 1);
        ancestor.resize(N + 1);
        std::iota(parents.begin(), parents.end(), 0);
        std::fill(ranks.begin(), ranks.end(), 0);
        std::fill(ancestor.begin(), ancestor.end(), 0);

        bool isAnswered = false;
        lca(root, x, y, adj, isAnswered);
    }

    return 0;
}