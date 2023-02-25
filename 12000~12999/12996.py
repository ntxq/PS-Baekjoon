'''
Subproblem:
    dp[N][a][b][c] = Number of ways to sing N songs with a, b, c songs for each of the three singers
Recurrence:
    dp[N][a][b][c] = 
        Singer A sing + Singer B sing + Singer C sing
        + (A and B sing) + (A and C sing) + (B and C sing)
        + (A, B, C sing)
'''


(N, A, B, C) = map(int, input().split())
dp = [[[[0 for _ in range(C+1)] for _ in range(B+1)] for _ in range(A+1)] for _ in range(N+1)]
dp[0][0][0][0] = 1
for n in range(1, N + 1):
    for a in range(A + 1):
        for b in range(B + 1):
            for c in range(max(n - a - b, 0), C + 1):
                if a > 0:
                    dp[n][a][b][c] += dp[n-1][a-1][b][c]
                if b > 0:
                    dp[n][a][b][c] += dp[n-1][a][b-1][c]
                if c > 0:
                    dp[n][a][b][c] += dp[n-1][a][b][c-1]
                if a > 0 and b > 0:
                    dp[n][a][b][c] += dp[n-1][a-1][b-1][c]
                if a > 0 and c > 0:
                    dp[n][a][b][c] += dp[n-1][a-1][b][c-1]
                if b > 0 and c > 0:
                    dp[n][a][b][c] += dp[n-1][a][b-1][c-1]
                if a > 0 and b > 0 and c > 0:
                    dp[n][a][b][c] += dp[n-1][a-1][b-1][c-1]
                dp[n][a][b][c] %= 1000000007

print(dp[N][A][B][C])