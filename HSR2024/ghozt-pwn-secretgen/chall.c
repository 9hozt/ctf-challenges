#define _GNU_SOURCE
#include <stdio.h>
#include <sys/ptrace.h>
#include <dlfcn.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_BUFFER_SIZE 16

typedef struct Secret
{
    char name[MAX_BUFFER_SIZE];
    char *value;
    void (* function)(struct Secret *);
} SecretStruct;

void ignore_me_init_buffering()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void getFlag()
{
    FILE *f;
    char line[50];
    f =  fopen("/home/ctf/flag.txt", "r");
    if (f == NULL)
    {
        puts("Error - File not found");
        exit(EXIT_FAILURE);
    }
    while (fgets(line, 50, f) != NULL) {
        printf("%s", line);
    }
}
void cleanMemory(SecretStruct *s){
    memset(s->value,0,32);
    memset(s->name,0,16);
    free(s->value);
    printf("Memory cleaned - Work done !\n");
    exit(0);
}

int main(int argc, char *argv[])
{
    ignore_me_init_buffering();
    int randomData = open("/dev/random", O_RDONLY);
    SecretStruct *s = malloc(sizeof(SecretStruct));
    memset(s->name,'\0',16);
    s->value = malloc(32);
    s->function = cleanMemory;
    read(randomData,s->value,32);
    printf("Entry name:\n");
    read(0,s->name,100);
    printf("Here is your random data:\n%s\n",s->value);
    s->function(s);
    return 0;
}