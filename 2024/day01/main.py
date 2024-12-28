import sys
from collections import Counter

lines = []
file = open("input.txt")
s = file.read().strip()
lines = s.split('\n')

a_left = []
a_right = []
for line in lines:
	l, r = map(int, line.split())
	a_left.append(l)
	a_right.append(r)

#a_left.sort()
#a_right.sort()
# total = sum(abs(a-b) for  a,b in zip(a_left, a_right))

r = Counter(a_right)
total = 0
for num in a_left:
	total += num * r[num]


print(total)

