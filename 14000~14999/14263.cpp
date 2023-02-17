#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

struct Card {
    int sx, sy, tx, ty;

    Card()
        : sx(std::numeric_limits<int>::max()),
          sy(std::numeric_limits<int>::max()),
          tx(std::numeric_limits<int>::min()),
          ty(std::numeric_limits<int>::min()) {}
    explicit operator bool() const { return sx <= tx && sy <= ty; }

    void addPoint(int x, int y) {
        sx = std::min(sx, x);
        sy = std::min(sy, y);

        tx = std::max(tx, x);
        ty = std::max(ty, y);
    }
};

int charToIndex(char c) {
    if ('0' <= c && c <= '9')
        return c - '0';
    else if ('A' <= c && c <= 'Z')
        return c - 'A' + 10;
    else
        return c - 'a' + 36;
}

char indexTochar(int i) {
    if (0 <= i && i <= 9)
        return i + '0';
    else if (10 <= i && i <= 35)
        return i - 10 + 'A';
    else
        return i - 36 + 'a';
}

std::vector<Card> getCards(int N, int M,
                           const std::vector<std::vector<char>>& board) {
    std::vector<Card> cards(62);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (board[i][j] != '.')
                cards[charToIndex(board[i][j])].addPoint(i, j);

    return cards;
}

std::vector<std::vector<int>> getAdj(const auto& cards, const auto& board) {
    std::vector<std::vector<int>> adj(62);

    std::vector<bool> isUsed(62, false);
    for (int i = 0; i < 62; ++i) {
        if (!cards[i]) continue;

        auto [sx, sy, tx, ty] = cards[i];
        for (int j = sx; j <= tx; ++j)
            for (int k = sy; k <= ty; ++k)
                if (board[j][k] == '.') {
                    std::cout << "-1\n";
                    exit(0);
                } else if (board[j][k] != indexTochar(i) &&
                           !isUsed[charToIndex(board[j][k])]) {
                    adj[i].push_back(charToIndex(board[j][k]));
                    isUsed[charToIndex(board[j][k])] = true;
                }

        std::fill(isUsed.begin(), isUsed.end(), false);
    }

    return adj;
}

bool dfs(int u, auto& visited, auto& adj) {
    visited[u] = 1;
    for (int v : adj[u])
        if (visited[v] == 1)
            return true;
        else if (!visited[v] && dfs(v, visited, adj))
            return true;

    visited[u] = 2;
    return false;
}

std::vector<char> topologicalSort(const auto& card, const auto& adj) {
    std::vector<int> visited(62, 0);

    bool isCycle = false;
    for (int i = 0; i < 62 && !isCycle; ++i)
        if (!visited[i] && card[i]) isCycle = dfs(i, visited, adj);
    if (isCycle) return {'-', '1'};

    std::vector<int> indegree(62, 0);
    for (int i = 0; i < 62; ++i)
        for (int j : adj[i]) ++indegree[j];

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int i = 0; i < 62; ++i)
        if (!indegree[i] && card[i]) pq.push(i);

    std::vector<char> order;
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();

        for (int v : adj[u])
            if (!--indegree[v]) pq.push(v);

        order.push_back(indexTochar(u));
    }

    return order;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<char>> board(N, std::vector<char>(M));
    for (auto& row : board)
        for (auto& cell : row) std::cin >> cell;

    auto cards{getCards(N, M, board)};
    auto adj{getAdj(cards, board)};

    for (char c : topologicalSort(cards, adj)) std::cout << c;
    std::cout << '\n';

    return 0;
}
