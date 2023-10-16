#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define MAXSIZE 20

struct TLV
{
  int8_t tag;
  char value[MAXSIZE];
  int8_t len;
};

void ignore_me_buffering()
{
    setvbuf(stdout,NULL,_IONBF,0);
    setvbuf(stdin,NULL,_IONBF,0);
    setvbuf(stderr,NULL,_IONBF,0);  
}

void getFlag()
{
  FILE *f;
  char line[50];
  f =  fopen("/home/ctf/flag.txt", "r");
  if (f == NULL)
    {
    puts("Une erreur c'est produite");
    exit(EXIT_FAILURE);
  }
  while (fgets(line, 50, f) != NULL) {
    printf("%s", line);
  }
}


int main(int argc, char *argv[])
{
    ignore_me_buffering();
    struct TLV tlv;
    int l;
    tlv.tag = 0x42;
    tlv.len = MAXSIZE+1;
    l = read(STDIN_FILENO,tlv.value,tlv.len);
    printf("Are you sure of your value ?\n");
    puts("New value:\n");
    read(STDIN_FILENO,tlv.value,tlv.len);
    return EXIT_SUCCESS;  
}