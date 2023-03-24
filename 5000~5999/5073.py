import sys

isEnded = False
while not isEnded:
    xs = [*map(int, sys.stdin.readline().split())]
    xs.sort()

    [x, y, z] = xs
    if x == 0 and y == 0 and z == 0:
        isEnded = True
    elif x + y <= z:
        print("Invalid")
    elif x == y == z:
        print("Equilateral")
    elif x == y or y == z:
        print("Isosceles")
    else:
        print("Scalene")
    
