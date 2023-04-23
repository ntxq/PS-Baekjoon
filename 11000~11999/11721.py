line = input()
for i in range(len(line) // 10 + 1):
    print(line[i * 10: (i + 1) * 10])