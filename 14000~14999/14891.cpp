#include <algorithm>
#include <iostream>
#include <vector>

struct Gear {
    bool state[8];
    int top = 0;

    void rotate(int dir) {
        if (dir == 1)
            top = (top + 7) % 8;
        else
            top = (top + 1) % 8;
    }

    int right() { return state[(top + 2) % 8]; }
    int left() { return state[(top + 6) % 8]; }
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    Gear gears[4];
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 8; ++j) {
            char c;
            std::cin >> c;
            gears[i].state[j] = c == '1';
        }

    int K;
    std::cin >> K;

    for (int i = 0; i < K; ++i) {
        int gear, dir;
        std::cin >> gear >> dir;

        int curLeft = gears[gear - 1].left();
        int curDir = dir;
        for (int j = gear - 2; j >= 0; --j)
            if (curLeft != gears[j].right()) {
                curLeft = gears[j].left();
                gears[j].rotate(-curDir);
                curDir = -curDir;
            } else {
                break;
            }

        int curRight = gears[gear - 1].right();
        curDir = dir;
        for (int j = gear; j < 4; ++j)
            if (curRight != gears[j].left()) {
                curRight = gears[j].right();
                gears[j].rotate(-curDir);
                curDir = -curDir;
            } else {
                break;
            }

        gears[gear - 1].rotate(dir);
    }

    int score = 0;
    for (int i = 0; i < 4; ++i)
        if (gears[i].state[gears[i].top]) score += (1 << i);

    std::cout << score << '\n';

    return 0;
}