#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, K;
    std::cin >> N >> K;

    std::vector<std::vector<bool>> apples(N, std::vector<bool>(N));
    for (int i = 0; i < K; ++i) {
        int x, y;
        std::cin >> x >> y;

        apples[x - 1][y - 1] = true;
    }

    int L;
    std::cin >> L;

    std::deque<std::pair<int, char>> moves(L);
    for (auto& move : moves) std::cin >> move.first >> move.second;

    std::deque<std::pair<int, int>> snake;
    std::vector<std::vector<bool>> occupied(N, std::vector<bool>(N));

    int dx = 0, dy = 1;
    snake.push_back({0, 0});
    occupied[0][0] = true;

    bool isDead = false;
    int time = 0;
    while (!isDead) {
        ++time;

        int nx = snake.front().first + dx;
        int ny = snake.front().second + dy;

        if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
            isDead = true;
            break;
        }

        if (occupied[nx][ny]) {
            isDead = true;
            break;
        }

        if (apples[nx][ny]) {
            occupied[nx][ny] = true;
            apples[nx][ny] = false;
            snake.push_front({nx, ny});
        } else {
            occupied[nx][ny] = true;
            snake.push_front({nx, ny});
            occupied[snake.back().first][snake.back().second] = false;
            snake.pop_back();
        }

        if (time == moves.front().first) {
            if (moves.front().second == 'L') {
                std::swap(dx, dy);
                dx *= -1;
            } else {
                std::swap(dx, dy);
                dy *= -1;
            }
            moves.pop_front();
        }
    }

    std::cout << time << '\n';

    return 0;
}