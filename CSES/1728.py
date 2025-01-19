import math
n = int(input())
r = list(map(int, input().split()))

def add(a, b):
    tmp = (a[0] * b[1] + b[0] * a[1], a[1] * b[1])
    g = math.gcd(tmp[0], tmp[1])
    return (tmp[0] // g, tmp[1] // g)

ans = (0, 1)
for i in range(n):
    for j in range(i + 1, n):
        t = min(r[i], r[j])
        ans = add(ans, (r[i] * t - t * (1 + t) // 2, r[i] * r[j]))

u, v = ans
u *= (10 ** 6)
quo, res = u // v, u % v
if res * 2 > v or (res * 2 == v and quo % 2 == 1):
    quo += 1
print(f'{quo / 1e6:06f}')
