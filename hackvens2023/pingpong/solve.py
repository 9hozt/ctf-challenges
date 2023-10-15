base = [141, 162, 236, 73, 78, 226, 77, 172, 202, 235, 237, 160, 10, 44, 202, 238, 130, 2, 206, 2, 10, 142, 130, 104, 43]

def unpingrot(s):
    return s[-5:]+s[:20]

def unpongrot(s):
    return s[-5:]+s[-13:-5]+s[:12]

def xor(s,TTL):
    return [i ^ TTL for i in s]

def transfo(n,r): #  ((str[i] >> r) + ((str[i]  & ((1 << r) -1)) << (8-r)))
    return((n >> r) + ((n & (2**r -1)) << (8-r)))

def unping(s,TTL):
    t = unpingrot(s)
    u = [transfo(i,5) for i in t]
    v = xor(u,TTL)
    return v

def unpong(s,TTL):
    t = unpongrot(s)
    u = xor(t,6)
    v = [transfo(i,1) for i in u]
    w = xor(v,TTL)
    return w

s = base
for i in range(0,25,2):
    s = unping(s,i)
    print("".join(chr(x) for x in s))
    s = unpong(s,i+1)
    #print("".join(chr(x) for x in s))

