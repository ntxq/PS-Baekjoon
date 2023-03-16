import sys

lines = sys.stdin.readlines()
lines = [line.strip() for line in lines]

maxLen = max([len(line) for line in lines])
for i in range(maxLen):
    chars: list[str] = []
    for line in lines:
        if len(line) > i:
            chars.append(line[i])
    
    print(''.join(chars), end='')