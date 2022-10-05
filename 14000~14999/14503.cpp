#include <algorithm>
#include <iostream>
#include <vector>

class Robot {
   public:
    enum Direction { NORTH, EAST, SOUTH, WEST };

    Robot(int r, int c, Direction d, const std::vector<std::vector<bool>>& room,
          int N, int M)
        : r(r),
          c(c),
          d(d),
          N(N),
          M(M),
          room(room),
          cleaned(std::vector<std::vector<bool>>(N, std::vector<bool>(M))) {}

    int clean() {
        while (work())
            ;
        return count;
    }

    bool work() {
        if (!cleaned[r][c]) {
            cleaned[r][c] = true;
            ++count;
        }

        for (int i = 0; i < 4; ++i) {
            rotate();
            auto [nx, ny] = next();
            if (!room[nx][ny] && !cleaned[nx][ny]) {
                r = nx;
                c = ny;
                return true;
            }
        }

        auto [nx, ny] = back();
        if (!room[nx][ny]) {
            r = nx;
            c = ny;
            return true;
        }

        return false;
    }

    Direction rotate() {
        switch (d) {
            case NORTH:
                d = WEST;
                break;
            case EAST:
                d = NORTH;
                break;
            case SOUTH:
                d = EAST;
                break;
            case WEST:
                d = SOUTH;
                break;
        }
        return d;
    }

    std::pair<int, int> next() {
        switch (d) {
            case NORTH:
                return {r - 1, c};
            case EAST:
                return {r, c + 1};
            case SOUTH:
                return {r + 1, c};
            case WEST:
                return {r, c - 1};
        }

        return {r, c};
    }

    std::pair<int, int> back() {
        switch (d) {
            case NORTH:
                return {r + 1, c};
            case EAST:
                return {r, c - 1};
            case SOUTH:
                return {r - 1, c};
            case WEST:
                return {r, c + 1};
        }

        return {r, c};
    }

   private:
    int r;
    int c;
    Direction d;

    const int N;
    const int M;
    std::vector<std::vector<bool>> room;
    std::vector<std::vector<bool>> cleaned;

    int count = 0;
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    int r, c, d;
    std::cin >> r >> c >> d;

    std::vector<std::vector<bool>> room(N, std::vector<bool>(M));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) {
            int x;
            std::cin >> x;
            room[i][j] = x == 1;
        }

    Robot robot(r, c, static_cast<Robot::Direction>(d), room, N, M);
    std::cout << robot.clean() << '\n';

    return 0;
}