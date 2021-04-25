'''
from math import *
a = int(input())
print(floor(log(a)/log(2)))
'''
from math import *
for a in range(1, 256):
    print(a, floor(log(a)/log(2)))
