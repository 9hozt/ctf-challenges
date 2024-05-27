BITS 64
section .bss
    buffer resb 16

section .data
        ; $ xortool-xor -r "J3r3m1e_1ns1d3R" -s "\x0f\x0e\x0d\x0c\x0b\x0a\x09\x08\x07\x06\x05\x04\x03\x02\x01"
    ;    E=?f;lW6hv5g1S
    str1 db 0x45, 0x3d, 0x7f, 0x3f , 0x66, 0x3b , 0x6c, 0x57 , 0x36, 0x68 , 0x76, 0x35 , 0x67, 0x31 , 0x53, 0x00

section .text
global _start

_start:
    xor rax, rax           ; rax = 0 (sys_read)
    mov rdi, rax           ; rdi = 0 (stdin)
    lea rsi, [rel buffer]  ; rsi buffer
    mov rdx, 15           ; rdx = size
    syscall

    lea rbx, [rel buffer]
    lea rsi, [rel str1]
    mov rcx, 15
    xor rdi,rdi
compare_loop:
    mov rax, rcx
    xor rdx,rdx
    xor al, byte [rsi]
    mov dl, byte [rbx]
    cmp al, dl
    jne exit
    inc rsi
    inc rbx
    dec rcx
    cmp rcx, 0
    jne compare_loop
    mov rdi, -1

shell:
    xor rsi,rsi
    xor rdi,rdi
    push rsi
    mov rdi,0x68732f2f6e69622f
    push rdi
    push rsp
    pop rdi
    push 59
    pop rax
    cdq
    syscall

exit:
    mov rax, 60            ; rax = 60 (sys_exit)
    syscall