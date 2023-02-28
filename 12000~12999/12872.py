from functools import cache

'''
Subproblem:
    dp[l][p] = Number of playlists of length l with p unique songs
Recurrence:
    dp[l][p] = 
        dp[l-1][p-1] * (n-p) # Add a new song
        + dp[l-1][p] * max(p-m, 0) # Add a song that's already in the playlist
'''

(n, m, p) = map(int, input().split())


@cache
def dp(l: int, k: int) -> int:
    if l == 0:
        return 1 if k == 0 else 0
    if k == 0 or k > l:
        return 0
    
    return dp(l-1, k-1) * (n-k+1) + dp(l-1, k) * max(k-m, 0)

print(dp(p, n) % 1000000007)