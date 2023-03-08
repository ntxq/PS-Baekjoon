n, m = map(int, input().split())
baskets = list(range(n))

for _ in range(m):
    a, b = map(int, input().split())
    a -= 1
    b -= 1

    tmp = baskets[a]
    baskets[a] = baskets[b]
    baskets[b] = tmp

for x in baskets:
    print(x + 1, end=' ')