# Subproblem: dp[i][j] = Number of people transportable using i trains for 0..j carts
# Recurrece: dp[i][j] = max(dp[i][j-1], dp[i-1][j-m] + sum(train[j-m+1:j+1]))

def loop(n: int, train: list[int], sublen: int) -> int:
    dp = [[0] * n for _ in range(3)]

    prefixSum = [0] * n
    prefixSum[0] = train[0]
    for i in range(1, n):
        prefixSum[i] = prefixSum[i-1] + train[i]

    for i in range(3):
        for j in range((i + 1) * sublen - 1, n):
            curPop = dp[i-1][j-sublen] if j >= sublen else 0
            curPop += prefixSum[j] - \
                (prefixSum[j-sublen] if j >= sublen else 0)
            dp[i][j] = max(dp[i][j-1], curPop)

    return dp[2][n-1]


def main() -> None:
    from sys import stdin

    n = int(stdin.readline())
    train = list(map(int, stdin.readline().split()))
    sublen = int(stdin.readline())
    print(loop(n, train, sublen))


if __name__ == "__main__":
    main()
