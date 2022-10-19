#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

char directions[4] = {'u', 'd', 'l', 'r'};

struct Camera {
    int type;
    int y, x;
    char direction;
};

void watch(const Camera& camera, std::vector<std::vector<int>>& room) {
    if (camera.type == 1) {
        if (camera.direction == 'u')
            for (int i = camera.y - 1; i >= 0 && room[i][camera.x] != 6; --i)
                room[i][camera.x] = -1;
        else if (camera.direction == 'd')
            for (int i = camera.y + 1;
                 i < room.size() && room[i][camera.x] != 6; ++i)
                room[i][camera.x] = -1;
        else if (camera.direction == 'l')
            for (int i = camera.x - 1; i >= 0 && room[camera.y][i] != 6; --i)
                room[camera.y][i] = -1;
        else if (camera.direction == 'r')
            for (int i = camera.x + 1;
                 i < room[0].size() && room[camera.y][i] != 6; ++i)
                room[camera.y][i] = -1;
    } else if (camera.type == 2) {
        if (camera.direction == 'u' || camera.direction == 'd') {
            for (int i = camera.y - 1; i >= 0 && room[i][camera.x] != 6; --i)
                room[i][camera.x] = -1;
            for (int i = camera.y + 1;
                 i < room.size() && room[i][camera.x] != 6; ++i)
                room[i][camera.x] = -1;
        } else if (camera.direction == 'l' || camera.direction == 'r') {
            for (int i = camera.x - 1; i >= 0 && room[camera.y][i] != 6; --i)
                room[camera.y][i] = -1;
            for (int i = camera.x + 1;
                 i < room[0].size() && room[camera.y][i] != 6; ++i)
                room[camera.y][i] = -1;
        }
    } else if (camera.type == 3) {
        if (camera.direction == 'u') {
            for (int i = camera.y - 1; i >= 0 && room[i][camera.x] != 6; --i)
                room[i][camera.x] = -1;
            for (int i = camera.x + 1;
                 i < room[0].size() && room[camera.y][i] != 6; ++i)
                room[camera.y][i] = -1;
        } else if (camera.direction == 'd') {
            for (int i = camera.y + 1;
                 i < room.size() && room[i][camera.x] != 6; ++i)
                room[i][camera.x] = -1;
            for (int i = camera.x - 1; i >= 0 && room[camera.y][i] != 6; --i)
                room[camera.y][i] = -1;
        } else if (camera.direction == 'l') {
            for (int i = camera.x - 1; i >= 0 && room[camera.y][i] != 6; --i)
                room[camera.y][i] = -1;
            for (int i = camera.y - 1; i >= 0 && room[i][camera.x] != 6; --i)
                room[i][camera.x] = -1;
        } else if (camera.direction == 'r') {
            for (int i = camera.x + 1;
                 i < room[0].size() && room[camera.y][i] != 6; ++i)
                room[camera.y][i] = -1;
            for (int i = camera.y + 1;
                 i < room.size() && room[i][camera.x] != 6; ++i)
                room[i][camera.x] = -1;
        }
    } else if (camera.type == 4) {
        if (camera.direction == 'u') {
            for (int i = camera.y - 1; i >= 0 && room[i][camera.x] != 6; --i)
                room[i][camera.x] = -1;
            for (int i = camera.x + 1;
                 i < room[0].size() && room[camera.y][i] != 6; ++i)
                room[camera.y][i] = -1;
            for (int i = camera.x - 1; i >= 0 && room[camera.y][i] != 6; --i)
                room[camera.y][i] = -1;
        } else if (camera.direction == 'd') {
            for (int i = camera.y + 1;
                 i < room.size() && room[i][camera.x] != 6; ++i)
                room[i][camera.x] = -1;
            for (int i = camera.x - 1; i >= 0 && room[camera.y][i] != 6; --i)
                room[camera.y][i] = -1;
            for (int i = camera.x + 1;
                 i < room[0].size() && room[camera.y][i] != 6; ++i)
                room[camera.y][i] = -1;
        } else if (camera.direction == 'l') {
            for (int i = camera.x - 1; i >= 0 && room[camera.y][i] != 6; --i)
                room[camera.y][i] = -1;
            for (int i = camera.y - 1; i >= 0 && room[i][camera.x] != 6; --i)
                room[i][camera.x] = -1;
            for (int i = camera.y + 1;
                 i < room.size() && room[i][camera.x] != 6; ++i)
                room[i][camera.x] = -1;
        } else if (camera.direction == 'r') {
            for (int i = camera.x + 1;
                 i < room[0].size() && room[camera.y][i] != 6; ++i)
                room[camera.y][i] = -1;
            for (int i = camera.y - 1; i >= 0 && room[i][camera.x] != 6; --i)
                room[i][camera.x] = -1;
            for (int i = camera.y + 1;
                 i < room.size() && room[i][camera.x] != 6; ++i)
                room[i][camera.x] = -1;
        }
    } else if (camera.type == 5) {
        for (int i = camera.y - 1; i >= 0 && room[i][camera.x] != 6; --i)
            room[i][camera.x] = -1;
        for (int i = camera.y + 1; i < room.size() && room[i][camera.x] != 6;
             ++i)
            room[i][camera.x] = -1;
        for (int i = camera.x - 1; i >= 0 && room[camera.y][i] != 6; --i)
            room[camera.y][i] = -1;
        for (int i = camera.x + 1; i < room[0].size() && room[camera.y][i] != 6;
             ++i)
            room[camera.y][i] = -1;
    }
}

int backtrack(unsigned idx, std::vector<Camera>& cameras,
              const std::vector<std::vector<int>>& room) {
    if (idx == cameras.size()) {
        auto curRoom = room;
        for (const auto& camera : cameras) watch(camera, curRoom);
        int cnt = 0;
        for (const auto& row : curRoom)
            for (const auto& cell : row)
                if (cell == 0) ++cnt;
        return cnt;
    }

    int minCnt = 64;
    for (int i = 0; i < 4; ++i) {
        cameras[idx].direction = directions[i];
        minCnt = std::min(minCnt, backtrack(idx + 1, cameras, room));
    }

    return minCnt;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> room(N, std::vector<int>(M, 0));
    std::vector<Camera> cameras;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) {
            int input;
            std::cin >> input;

            room[i][j] = input;
            if (input != 0 && input != 6) cameras.push_back({input, i, j, 'U'});
        }

    std::cout << backtrack(0, cameras, room) << '\n';

    return 0;
}