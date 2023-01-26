#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

using std::vector;

struct Player {
    int position;
    int routeNumber;

    Player() : position(0), routeNumber(0) {}

    int move(int movement) {
        if (routeNumber == 1) {
            int curIdx = (position - 10) / 3;
            int nextIdx = curIdx + movement;

            switch (nextIdx) {
                case 1:
                    return position = 13;
                case 2:
                    return position = 16;
                case 3:
                    return position = 19;
                default:
                    position = 25 + (nextIdx - 4) * 5;
                    routeNumber = position == 40 ? 0 : 4;
                    return position > 40 ? 0 : position;
            }
        } else if (routeNumber == 2) {
            int curIddx = (position - 20) / 2;
            int nextIdx = curIddx + movement;

            switch (nextIdx) {
                case 1:
                    return position = 22;
                case 2:
                    return position = 24;
                default:
                    position = 25 + (nextIdx - 3) * 5;
                    routeNumber = position == 40 ? 0 : 4;
                    return position > 40 ? 0 : position;
            }
        } else if (routeNumber == 3) {
            int curIdx;
            switch (position) {
                case 30:
                    curIdx = 0;
                    break;
                case 28:
                    curIdx = 1;
                    break;
                case 27:
                    curIdx = 2;
                    break;
                case 26:
                    curIdx = 3;
                    break;
            }

            int nextIdx = curIdx + movement;

            switch (nextIdx) {
                case 1:
                    return position = 28;
                case 2:
                    return position = 27;
                case 3:
                    return position = 26;
                default:
                    position = 25 + (nextIdx - 4) * 5;
                    routeNumber = position == 40 ? 0 : 4;
                    return position > 40 ? 0 : position;
            }
        } else if (routeNumber == 4) {
            position += movement * 5;
            routeNumber = position == 40 ? 0 : 4;
            return position > 40 ? 0 : position;
        }

        position += movement * 2;

        if (position == 10)
            routeNumber = 1;
        else if (position == 20)
            routeNumber = 2;
        else if (position == 30)
            routeNumber = 3;

        return position > 40 ? 0 : position;
    }

    friend bool operator==(const Player& lhs, const Player& rhs) {
        return lhs.position == rhs.position &&
               lhs.routeNumber == rhs.routeNumber && lhs.position < 41 &&
               rhs.position < 41;
    }

    friend bool canMove(int playerId, int movement, vector<Player>& players) {
        int prevPos = players[playerId].position;
        int prevRoute = players[playerId].routeNumber;

        players[playerId].move(movement);

        bool canMove = true;
        for (int i = 0; i < 4 && canMove; ++i)
            if (i != playerId && players[i] == players[playerId])
                canMove = false;

        players[playerId].position = prevPos;
        players[playerId].routeNumber = prevRoute;

        return canMove;
    }
};

int backtrack(int idx, vector<Player>& players, const vector<int>& movements) {
    if (idx == 10) return 0;

    int curMovement = movements[idx];
    int bestScore = std::numeric_limits<int>::min();

    for (int i = 0; i < 4; ++i)
        if (canMove(i, curMovement, players)) {
            int prevPos = players[i].position;
            int prevRoute = players[i].routeNumber;

            bestScore =
                std::max(bestScore, players[i].move(curMovement) +
                                        backtrack(idx + 1, players, movements));

            players[i].position = prevPos;
            players[i].routeNumber = prevRoute;
        }

    return bestScore;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    vector<int> movements(10);
    for (auto& m : movements) std::cin >> m;

    vector<Player> players(4);

    std::cout << backtrack(0, players, movements) << '\n';

    return 0;
}