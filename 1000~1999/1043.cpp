#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef std::vector<std::vector<int>> Matrix;

void bfs(std::vector<bool>& people, std::queue<int>& q, const Matrix& party,
         const Matrix& adj) {
    while (!q.empty()) {
        int person = q.front();
        q.pop();

        for (const auto& joined : adj[person])
            for (const auto& friends : party[joined])
                if (!people[friends]) {
                    people[friends] = true;
                    q.push(friends);
                }
    }
}

int countParty(std::vector<bool>& people, const Matrix& party) {
    int count = 0;
    for (const auto& friends : party)
        for (const auto& person : friends)
            if (!people[person]) {
                ++count;
                break;
            }

    return count;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<bool> people(n);
    std::queue<int> q;

    int known;
    std::cin >> known;
    for (int i = 0; i < known; ++i) {
        int k;
        std::cin >> k;

        people[k - 1] = true;
        q.push(k - 1);
    }

    Matrix party(m);
    Matrix adj(n);
    for (int i = 0; i < m; ++i) {
        int size;
        std::cin >> size;

        for (int j = 0; j < size; ++j) {
            int k;
            std::cin >> k;

            party[i].push_back(k - 1);
            adj[k - 1].push_back(i);
        }
    }

    bfs(people, q, party, adj);
    std::cout << countParty(people, party);

    return 0;
}