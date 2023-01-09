#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

std::vector<int> cube(24);

bool check() {
    for (int i = 0; i < 24; ++i)
        if (cube[i] != cube[i / 4 * 4]) 
            return false;
    return true;
}

void rotate1() {
    int temp1 = cube[20];
    int temp2 = cube[22];

    cube[20] = cube[3];
    cube[22] = cube[1];

    cube[3] = cube[7];
    cube[1] = cube[5];

    cube[5] = cube[9];
    cube[7] = cube[11];

    cube[11] = temp1;
    cube[9] = temp2;
}

void rotate2() {
    int temp1 = cube[21];
    int temp2 = cube[23];
    cube[21] = cube[2];
    cube[23] = cube[0];

    cube[2] = cube[6];
    cube[0] = cube[4];

    cube[6] = cube[10];
    cube[4] = cube[8];

    cube[10] = temp1;
    cube[8] = temp2;
}

void rotate3() {
    int temp1 = cube[10];
    int temp2 = cube[11];
    cube[10] = cube[12];
    cube[11] = cube[14];

    cube[12] = cube[1];
    cube[14] = cube[0];

    cube[1] = cube[19];
    cube[0] = cube[17];

    cube[19] = temp1;
    cube[17] = temp2;
}

void rotate4() {
    int temp1 = cube[8];
    int temp2 = cube[9];

    cube[8] = cube[13];
    cube[9] = cube[15];

    cube[13] = cube[3];
    cube[15] = cube[2];

    cube[3] = cube[18];
    cube[2] = cube[16];

    cube[18] = temp1;
    cube[16] = temp2;
}

void rotate5() {
    int temp1 = cube[18];
    int temp2 = cube[19];

    cube[19] = cube[23];
    cube[18] = cube[22];

    cube[23] = cube[15];
    cube[22] = cube[14];

    cube[15] = cube[7];
    cube[14] = cube[6];

    cube[7] = temp2;
    cube[6] = temp1;
}

void rotate6() {
    int temp = cube[17];
    int temp2 = cube[16];

    cube[17] = cube[21];
    cube[16] = cube[20];

    cube[21] = cube[13];
    cube[20] = cube[12];

    cube[12] = cube[4];
    cube[13] = cube[5];

    cube[4] = temp2;
    cube[5] = temp;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<void (*)()> rotations{rotate1, rotate2, rotate3,
                                      rotate4, rotate5, rotate6};

    for (auto& i : cube) std::cin >> i;

    bool isSolved = false;
    for (int i = 0; i < 6; ++i) {
        rotations[i]();
        isSolved |= check();
        rotations[i]();
        rotations[i]();
        isSolved |= check();
        rotations[i]();
    }

    std::cout << isSolved << '\n';

    return 0;
}
