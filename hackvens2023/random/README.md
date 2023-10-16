# Random ?

## The bug

In this challenge, 30 bytes are read from /dev/random, then the user is acked for an input that will be compared with these random bytes.

The fact is that there is a one in 256 chance that the first random byte to be a null byte.
As strcmp is used, and a memory string ends with a nullbyte, a good straetgy is to send only one null byte in a loop and wait for the flag :)