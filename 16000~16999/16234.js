const fs = require('fs')

const input = fs.readFileSync('/dev/stdin').toString().split(/\s+/).map(x => parseInt(x))
const [N, L, R, ...rest] = input

/**
 * 
 * @param {number} x 
 * @param {number} y 
 * @param {number[][]} board 
 * @param {number[][]} visited
 * @param {number} group
 * @returns 
 */
function bfs(x, y, board, visited, group) {
    const dx = [0, 0, -1, 1]
    const dy = [-1, 1, 0, 0]

    const queue = [[x, y]]
    visited[x][y] = group

    let isModified = false
    while (queue.length > 0) {
        const [x, y] = queue.shift()
        for (let i = 0; i < 4; ++i) {
            const nx = x + dx[i]
            const ny = y + dy[i]
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue

            const diff = Math.abs(board[x][y] - board[nx][ny])
            if (diff >= L && diff <= R && visited[nx][ny] == 0) {
                isModified = true
                visited[nx][ny] = group
                queue.push([nx, ny])
            }
        }
    }

    return isModified
}

/**
 * 
 * @param {number[][]} board 
 * @param {number[][]} visited 
 * @param {number} group
 */
function transition(board, visited, group) {
    const sum = Array(group).fill(0)
    const count = Array(group).fill(0)

    for (let i = 0; i < N; ++i)
        for (let j = 0; j < N; ++j)
            if (visited[i][j] > 0) {
                sum[visited[i][j] - 1] += board[i][j]
                ++count[visited[i][j] - 1]
            }

    for (let i = 0; i < N; ++i)
        for (let j = 0; j < N; ++j)
            if (visited[i][j] > 0)
                board[i][j] = Math.floor(sum[visited[i][j] - 1] / count[visited[i][j] - 1])
}

function solve() {
    const board = Array.from({ length: N }, (_, i) => rest.slice(i * N, (i + 1) * N))

    let answer = 0
    let isModified = true
    while (isModified) {
        const visited = Array.from({ length: N }, () => Array(N).fill(0))
        let group = 0
        isModified = false

        for (let i = 0; i < N; ++i)
            for (let j = 0; j < N; ++j)
                if (visited[i][j] == 0)
                    isModified |= bfs(i, j, board, visited, ++group)


        if (isModified) ++answer
        transition(board, visited, group)
    }

    console.log(answer)
}

solve()