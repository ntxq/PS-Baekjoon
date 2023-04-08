n1, d1 = map(int, input().split())
n2, d2 = map(int, input().split())

ns = n1 * d2 + n2 * d1
ds = d1 * d2

from math import gcd
g = gcd(ns, ds)
print(ns // g, ds // g)