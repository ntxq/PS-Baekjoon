dancing: set[str] = set()
dancing.add("ChongChong")

for _ in range(int(input())):
    x, y = input().split()
    if x in dancing:
        dancing.add(y)
    elif y in dancing:
        dancing.add(x)

print(len(dancing))