def hanoi_sequence(frm, to, aux, size):
    if size == 0:
        return
    
    hanoi_sequence(frm, aux, to, size - 1)
    print(frm, to, sep=' ')
    hanoi_sequence(aux, to, frm, size - 1)
    
    return

N = int(input())

print((1 << N) - 1)
if N <= 20:
    hanoi_sequence(1, 3, 2, N)