# AreUBlind

Blind remote format string challenge.

It is possible to trig an OBO bug to control the input format, then dump the stack to find interessting pointers to craft a write what where.

Identifying libc, then ROP system("/bin/sh") or use one gadget

