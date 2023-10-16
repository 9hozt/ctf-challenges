from pwn import *

while(1):
    r = remote("15.237.218.78", 1337)
    r.send(b"\x00")
    try:
        print(r.recvall())
    except:
        r.close()

