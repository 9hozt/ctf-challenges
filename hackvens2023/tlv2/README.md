# TLV2

## The bug

The bug is in  the get_tag function. The scanf cast input as long (16 bytes) but tag element in the stucture is of type int (8 bytes) leading to an overflow on the following element in the structure (pointer to the value).

With that bug, it is possible to "write what where" when the "get_value" function is called.

The difficulty lies in the fact that "free" must receive an address that can be freed.

A strategy could be :
   - overwrite free with main
   - overwrite exit with main
   - overwrite free with printf

At that point, you can leak whatever you want with format string, leak libc, get system, pop shell :)
