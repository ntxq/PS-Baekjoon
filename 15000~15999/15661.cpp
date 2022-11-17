#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int N;

int teamDiff(const std::vector<std::vector<int>>& scores,
             const std::vector<bool>& visited) {
    int team1 = 0;
    int team2 = 0;

    for (int i = 0; i < N - 1; i++)
        for (int j = i + 1; j < N; j++)
            if (visited[i] && visited[j])
                team1 += scores[i][j] + scores[j][i];
            else if (!visited[i] && !visited[j])
                team2 += scores[i][j] + scores[j][i];

    return abs(team1 - team2);
}

int minTeamDiff(const std::vector<std::vector<int>>& scores,
                std::vector<bool>& visited, int idx) {
    if (idx == N) return teamDiff(scores, visited);

    int team1 = minTeamDiff(scores, visited, idx + 1);
    visited[idx] = true;
    int team2 = minTeamDiff(scores, visited, idx + 1);
    visited[idx] = false;

    return std::min(team1, team2);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::cin >> N;

    std::vector<std::vector<int>> scores(N, std::vector<int>(N));
    for (auto& row : scores)
        for (auto& score : row) std::cin >> score;

    std::vector<bool> visited(N, false);
    std::cout << minTeamDiff(scores, visited, 0) << '\n';

    return 0;
}