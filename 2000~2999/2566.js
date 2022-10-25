const fs = require('fs')

const input = fs.readFileSync('/dev/stdin').toString().split(/\s+/).map(x => parseInt(x))

let idx = 0
for (let i = 1; i < input.length; ++i)
    if (input[i] > input[idx])
        idx = i

console.log(input[idx])
console.log(`${Math.floor(idx / 9) + 1} ${idx % 9 + 1}`)