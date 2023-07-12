# Configuration Loader

Challenge with several bugs: 

 - Buffer overflow to bypass the authentication
 - read(3) off-by-one to overwrite \0 on path buffer
 - Path traversal to fillfull the path buffer with a valid UNIX path
 - Read /etc/passwd to obtain the user home path
 - Read the flag file and profit :)


