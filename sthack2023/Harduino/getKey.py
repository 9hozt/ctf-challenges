base = "Z7cX_Ud-3A5E'1m)=?cJU664";
key = []

for i in range(0,len(base)):
    tmp = i ^ ord(base[i])
    if tmp <= 32:
        tmp = tmp + 31
    if tmp >= 126:
        tmp = tmp - 125
    key.append(tmp)

print(''.join(chr(x) for x in key))

