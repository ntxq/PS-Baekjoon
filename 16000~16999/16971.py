def solve(matrix: list[list[int]]) -> int:
    rowSums = [sum(row) for row in matrix]
    colSums = [sum(col) for col in zip(*matrix)]

    totalSum = sum(rowSums) * 4 - rowSums[0] * 2 - rowSums[-1] * 2 - colSums[0] * 2 - colSums[-1] * 2 \
        + matrix[0][0] + matrix[0][-1] + matrix[-1][0] + matrix[-1][-1]

    maxRow = 0 if rowSums[0] > rowSums[-1] else -1
    maxRowVal = rowSums[maxRow] * 4 - matrix[maxRow][0] * 2 - matrix[maxRow][-1] * 2
    minRowVal = maxRowVal
    
    for i in range(1, len(matrix) - 1):
        curRowVal = rowSums[i] * 4 - matrix[i][0] * 2 - matrix[i][-1] * 2
        if curRowVal < minRowVal:
            minRowVal = curRowVal

    maxCol = 0 if colSums[0] > colSums[-1] else -1
    maxColVal = colSums[maxCol] * 4 - matrix[0][maxCol] * 2 - matrix[-1][maxCol] * 2
    minColVal = maxColVal

    for i in range(1, len(matrix[0]) - 1):
        curColVal = colSums[i] * 4 - matrix[0][i] * 2 - matrix[-1][i] * 2
        if curColVal < minColVal:
            minColVal = curColVal

    rowDelta = (maxRowVal - minRowVal) // 2
    colDelta = (maxColVal - minColVal) // 2

    return totalSum + max(rowDelta, colDelta)


[n, m] = [int(x) for x in input().split()]
matrix = [[int(x) for x in input().split()] for _ in range(n)]
print(solve(matrix))
