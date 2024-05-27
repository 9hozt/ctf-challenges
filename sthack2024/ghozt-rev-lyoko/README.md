# Code Lyoko

Reversing challenge embedding an obfuscated shellcode


## Solve

Shellcode is xored with an environnement variable which is reachable is a SIGFPE is triggered.

The send_mobs functions can lead to a div by 0

The shellcode asks for an input and xor it with a integer which is decrement until 0
