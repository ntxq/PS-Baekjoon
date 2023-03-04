import sys

for line in sys.stdin:
    higher, lower, number, space = 0, 0, 0, 0
    for char in line:
        if char.isupper():
            higher += 1
        elif char.islower():
            lower += 1
        elif char.isdigit():
            number += 1
        elif char.isspace():
            space += 1
    print(lower, higher, number, space - 1)