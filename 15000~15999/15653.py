import copy
from typing import Tuple


def isSafe(nx: int, ny: int, board: list[list[str]]) -> bool:
    return 0 <= nx < len(board) and 0 <= ny < len(board[0]) and board[nx][ny] == "."


def move(dir: str, board: list[list[str]]) -> Tuple[bool, bool, list[list[str]]]:
    dx, dy = 0, 0
    if dir == 'U':
        dx = -1
    elif dir == 'D':
        dx = 1
    elif dir == 'L':
        dy = -1
    elif dir == 'R':
        dy = 1

    rx, ry = 0, 0
    for i in range(len(board)):
        for j in range(len(board[0])):
            if board[i][j] == "R":
                rx, ry = i, j
                break

    isRedOut = False
    nx, ny = rx + dx, ry + dy
    while isSafe(nx, ny, board):
        board[nx][ny] = "R"
        board[rx][ry] = "."
        rx, ry = nx, ny
        nx, ny = rx + dx, ry + dy

    if 0 <= nx < len(board) and 0 <= ny < len(board[0]) and board[nx][ny] == "O":
        isRedOut = True
        board[rx][ry] = "."

    bx, by = 0, 0
    for i in range(len(board)):
        for j in range(len(board[0])):
            if board[i][j] == "B":
                bx, by = i, j
                break

    isBlueOut = False
    nx, ny = bx + dx, by + dy
    while isSafe(nx, ny, board):
        board[nx][ny] = "B"
        board[bx][by] = "."
        bx, by = nx, ny
        nx, ny = bx + dx, by + dy

    if 0 <= nx < len(board) and 0 <= ny < len(board[0]) and board[nx][ny] == "O":
        isBlueOut = True
        board[bx][by] = "."

    if not isRedOut:
        nx, ny = rx + dx, ry + dy
        while isSafe(nx, ny, board):
            board[nx][ny] = "R"
            board[rx][ry] = "."
            rx, ry = nx, ny
            nx, ny = rx + dx, ry + dy

        if 0 <= nx < len(board) and 0 <= ny < len(board[0]) and board[nx][ny] == "O":
            isRedOut = True
            board[rx][ry] = "."

    return (isRedOut, isBlueOut, board)


def bfs(board: list[list[str]]) -> int:
    q: list[list[list[str]]] = []
    visited: set[Tuple[int, int, int, int]] = set()

    rx, ry = 0, 0
    bx, by = 0, 0

    for i in range(len(board)):
        for j in range(len(board[0])):
            if board[i][j] == "R":
                rx, ry = i, j
            elif board[i][j] == "B":
                bx, by = i, j

    q.append(board)
    visited.add((rx, ry, bx, by))

    curDist = 0
    curSize = 0
    nextSize = 1

    while q:
        curSize = nextSize
        nextSize = 0
        curDist += 1

        for _ in range(curSize):
            curBoard = q.pop(0)

            for dir in ['U', 'D', 'L', 'R']:
                isRedOut, isBlueOut, nextBoard = move(
                    dir, copy.deepcopy(curBoard))
                if isRedOut and not isBlueOut:
                    return curDist
                elif not isBlueOut:
                    rx, ry = 0, 0
                    bx, by = 0, 0

                    for i in range(len(nextBoard)):
                        for j in range(len(nextBoard[0])):
                            if nextBoard[i][j] == "R":
                                rx, ry = i, j
                            elif nextBoard[i][j] == "B":
                                bx, by = i, j

                    if (rx, ry, bx, by) not in visited:
                        visited.add((rx, ry, bx, by))
                        q.append(nextBoard)
                        nextSize += 1

    return -1


def main() -> None:
    n, _ = map(int, input().split())
    board = [list(input()) for _ in range(n)]

    print(bfs(board))


if __name__ == "__main__":
    main()
