import numpy as np

n = int(input());
a = input().split();
b = input().split();
a.sort();
b.sort(reverse = True);
ans = 1;
for i in range(n):
	ans *= int(a[i]) + int(b[i]);
print(ans);
