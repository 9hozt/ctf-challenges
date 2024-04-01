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

typedef struct Auth
{
    char login[16];
    char passwd[16];
    int (*function)(char *login, char *passwd);
} AuthStruct;

void ignore_me_init_buffering()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

int authenticate(char *login, char *passwd)
{
    if (strncmp(passwd, "p@s5w0rd",8) == 0) {
        printf("OK!!\n");
        return 1;
    } else {
        return 0;
    }
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

    int is_auth = 0;
    int count = 0;

    AuthStruct  *a = malloc(sizeof(AuthStruct));
    a->function = authenticate;
    while(1) {
        memset(a->login, '\x00', 16);
        memset(a->passwd, '\x00', 16);
        printf("Login: \n");
        read(0, a->login, 16);
        printf("Password: \n");
        read(0, a->passwd, 16);
        is_auth = a->function(a->login, a->passwd);
        if (!is_auth){
            count += 1;
            printf("%s:%s are not valid credentials...", a->login, a->passwd);
        }
        else{
            is_auth = 1;
        }
        if (count >= 3) {
            printf("ACCOUNT LOCKED OUT, bye ...");
            exit(1);
        }
        if (is_auth)
        {
            break;
        }
    }
    if (!is_auth)
    {
        exit(1);
    }
    printf("Auth success\n");

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