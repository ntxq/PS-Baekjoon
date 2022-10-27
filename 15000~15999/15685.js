const fs = require('fs')

function solve() {
    const input = fs.readFileSync('/dev/stdin').toString().split(/\s+/).map(x => parseInt(x))

    const [N, ...rest] = input
    const curves = Array(N).fill(0).map((_, i) => rest.slice(i * 4, i * 4 + 4))

    const dx = [1, 0, -1, 0]
    const dy = [0, -1, 0, 1]

    const visited = Array(101).fill(0).map(() => Array(101).fill(false))
    for (const curve of curves) {
        const moves = getMoves(curve)

        let [x, y] = curve
        visited[x][y] = true

        for (const move of moves) {
            x += dx[move]
            y += dy[move]
            visited[x][y] = true
        }
    }

    console.log(countSquare(visited))
}

/**
 * 
 * @param {number[]} curve 
 * @returns {number[]}
 */
function getMoves(curve) {
    if (curve[3] === 0) return [curve[2]]

    const moves = getMoves([curve[0], curve[1], curve[2], curve[3] - 1])
    const reversed = [...moves].reverse().map(x => (x + 1) % 4)
    return [...moves, ...reversed]
}

/**
 * 
 * @param {boolean[][]} visited 
 * @returns {number}
 */
function countSquare(visited) {
    let count = 0
    for (let i = 0; i < 100; ++i)
        for (let j = 0; j < 100; ++j)
            if (visited[i][j] && visited[i + 1][j] && visited[i][j + 1] && visited[i + 1][j + 1])
                ++count
    return count
}

solve()