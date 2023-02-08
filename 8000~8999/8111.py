from queue import Queue


def bfs(s: int) -> str:
    q: Queue[tuple[int, str]] = Queue()
    visited: list[bool] = list(False for _ in range(s))

    q.put((1 % s, "1"))
    visited[1 % s] = True

    while not q.empty():
        u, path = q.get()

        if u == 0:
            return path

        v1 = (u * 10) % s
        if not visited[v1]:
            q.put((v1, path + "0"))
            visited[v1] = True

        v2 = (u * 10 + 1) % s
        if not visited[v2]:
            q.put((v2, path + "1"))
            visited[v2] = True

    return "BRAK"


def main() -> None:
    for _ in range(int(input())):
        print(bfs(int(input())))


main()
