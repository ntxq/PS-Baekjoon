#include <iostream>
#include <queue>

unsigned bfs(unsigned start, unsigned target) {
    unsigned visited[100001]{};

    std::queue<unsigned> q;
    q.push(start);
    visited[start] = 1;

    while (!q.empty() && !visited[target]) {
        unsigned cur = q.front();
        q.pop();

        if (cur > 0 && !visited[cur - 1]) {
            q.push(cur - 1);
            visited[cur - 1] = visited[cur] + 1;
        }

        if (cur < 100000 && !visited[cur + 1]) {
            q.push(cur + 1);
            visited[cur + 1] = visited[cur] + 1;
        }

        if (cur * 2 < 100001 && !visited[cur * 2]) {
            q.push(cur * 2);
            visited[cur * 2] = visited[cur] + 1;
        }
    }

    return visited[target] - 1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned start, target;
    std::cin >> start >> target;

    std::cout << bfs(start, target);

    return 0;
}