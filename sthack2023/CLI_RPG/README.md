# CLI RPG

This is a pwn challenge with three bugs to chain to obtain the flag.
 - A memory leak
 - A integer underflow
 - A buffer overflow

# Spot the bugs

The program act as a RPG like game, first it ask for a nickname, then provide a menu with various actions

The first bug is about a memory leak, indeed, when the programm ask for a nickname, it read stdin for the full size buffer. This leads to memory leak. 
According to the structure, we can leak a .text address that leads to PIE leak.

The buffer overflow in the 'chest' function can be access if you own 200 or more fragments.

The first menu input is just a rabbit hole that perform sleep() call and give yo uone fragment.

The second menu entry can allow to to a integer underflow and obtain more than 200 fragments.

Once this done, you can do a classic ROP to leak and identify libc, then [get a shell](./solve.py).
