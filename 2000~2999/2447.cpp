#include <algorithm>
#include <iostream>

void starSquare(int x, int y, int size, char** map) {
    if (size == 3) {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                map[x + i][y + j] = (i == 1 && j == 1) ? ' ' : '*';
        return;
    }

    int newSize = size / 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (i != 1 || j != 1)
                starSquare(x + i * newSize, y + j * newSize, newSize, map);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    char** map = new char*[N];
    for (int i = 0; i < N; ++i) {
        map[i] = new char[N];
        std::fill(map[i], map[i] + N, ' ');
    }

    starSquare(0, 0, N, map);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) std::cout << map[i][j];
        std::cout << '\n';
    }

    return 0;
}
