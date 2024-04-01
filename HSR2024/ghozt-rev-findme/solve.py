from z3 import *

flag = [BitVec(f'{i}', 8) for i in range(16)]

s = Solver()


s.add(flag[0] == ord('H'))
s.add(flag[1] == ord('S'))
s.add(flag[2] == ord('R'))
s.add(flag[3] == ord('{'))
s.add(flag[15] == ord('}'))

s.add((flag[0] ^ flag[15]) == 53)
s.add((flag[0] ^ flag[14]) == 105)

s.add((flag[1] ^ flag[14]) == 114)
s.add((flag[1] ^ flag[13]) == 96)

s.add((flag[2] ^ flag[13]) == 97)
s.add((flag[2] ^ flag[12]) == 31)

s.add((flag[3] ^ flag[12]) == 54)
s.add((flag[3] ^ flag[11]) == 36)

s.add((flag[4] ^ flag[11]) == 10)
s.add((flag[4] ^ flag[10]) == 17)

s.add((flag[5] ^ flag[10]) == 27)
s.add((flag[5] ^ flag[9]) == 17)

s.add((flag[6] ^ flag[9]) == 8)
s.add((flag[6] ^ flag[8]) == 19)

s.add((flag[7] ^ flag[8]) == 101)
s.add((flag[7] ^ flag[7]) == 0)

s.add((flag[8] ^ flag[7]) == 101)
s.add((flag[8] ^ flag[6]) == 19)
"""
53 et 105
114 et 96
97 et 31
54 et 36
10 et 17
27 et 17
8 et 19
101 et 0
101 et 19
8 et 17
27 et 17
10 et 36
54 et 31
97 et 96
114 et 105
53 et 125
"""

print(s.check())
model = s.model()

for i in range(16):
    ch = model[flag[i]].as_string()
    print(chr(int(ch)), end='')