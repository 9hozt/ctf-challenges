#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define MAXSIZE 20

struct TLV
{
  int len;
  int tag;
  char *value;
};

void get_tag(void *tag) {
  if (scanf("%ld%*c", (long*)tag) != 1) 
    exit(1);
}

void get_value(char **value) {
  size_t n;
  getline(value, &n, stdin);
  (*value)[strcspn(*value, "\n")] = '\0';
}


void ignore_me_buffering()
{
    setvbuf(stdout,NULL,_IONBF,0);
    setvbuf(stdin,NULL,_IONBF,0);
    setvbuf(stderr,NULL,_IONBF,0);  
}

int main(int argc, char *argv[])
{
    ignore_me_buffering();
    struct TLV tlv = { 0 };

    printf("TLV Tag: \n");
    get_tag(&tlv.tag);
    printf("TLV Value: \n");
    get_value(&tlv.value);
    tlv.len = strlen(tlv.value);
    printf("[%d|%d|%s]", tlv.tag,tlv.len,tlv.value);
    free(tlv.value);
    exit(EXIT_SUCCESS);
}