while True:
    line = input()
    N, C, M = line.split()
    N, M = int(N), int(M)
    if N == 0 and M == 0:
        break
    if C == '/':
        print(f'{N // M}...{N % M}')
    else:
        print(eval(line))
        
