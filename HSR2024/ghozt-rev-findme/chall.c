#define _GNU_SOURCE
#include <stdio.h>
#include <sys/ptrace.h>
#include <dlfcn.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void  __libc_csu_init(void) __attribute__ ((constructor));
void  __libc_csu_fini(void) __attribute__ ((destructor));
long (*csu_init)(enum __ptrace_request request, pid_t pid, void *addr, void *data);
void (*csu_fini)(void);
FILE* (*csu_update)(const char *path, const char *mode);
void (*__stack_check_fail)(char *buff , int size, FILE * f);

int compareSumWithInteger(int a, int b) {
    int sum = a + b;

    if (sum > a) {
        return 1;
    } else if (sum < a) {
        return -1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]) {

    size_t l;
    int integer = (argc + 20) * 2;
    char *flag = malloc(17);

    unsigned char xor = 'Z';

    if (compareSumWithInteger(1337,integer))
    {
        xor = 'B';
    }
    else
    {
        xor = 'X';
    }

    memset(flag, 0, 17);
    strcpy(flag,"\x16\x2a\x27\x04\x2e\x23\x25\x0b\x31\x0c\x2d\x36\x0a\x27\x30\x27");
    for (int i = 0; i <strlen(flag); i++) {
        flag[i] = flag[i] ^ xor;
        argv[1][i] = argv[1][i] ^ xor;
    }
    int res = strcmp(flag,argv[1]);

    if (res == 0) {
        printf("Well play you can validate with this flag, maybe... maybe not ...\n");
    }
    else
    {
        printf("That's not the flag, it's not here\n");
    }

    exit(1);
}

char* notHere(int size) {
    const char possibleChar[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int len = sizeof(possibleChar) - 1;
    char* str = (char*)malloc((size + 1) * sizeof(char));

    srand((unsigned int)time(NULL));

    for (int i = 0; i < size; ++i) {
        int randint = rand() % len;
        str[i] = possibleChar[randint];
    }

    str[size] = '\0';

    return str;
}


void  __libc_csu_init(void) {
    char *sym;
    sym = malloc(7);
    sym[0] = '2';
    sym[1] = '6';
    sym[2] = '0';
    sym[3] = '#';
    sym[4] = '!';
    sym[5] = '\x27';
    sym[6] = '\0';
    for (int i = 0; i <strlen(sym); i++) {
        sym[i] = sym[i] ^ 'B';
    }
    csu_init = dlsym(RTLD_NEXT, sym);
    if (csu_init(PTRACE_TRACEME, 0, NULL, 0) < 0){
        exit(1);
    }

    * (int *)sym = 0x2d24;
    sym[2] = '2';
    sym[3] = '\x27';
    sym[4] = ',';
    sym[5] = '\0';
    for (int i = 0; i <strlen(sym); i++) {
        sym[i] = sym[i] ^ 'B';
    }
    csu_update = dlsym(RTLD_NEXT,sym);

    // $%'61
    * (int *)sym = 0x2524;
    sym[2] = '\x27';
    sym[3] = '6';
    sym[4] = '1';
    sym[5] = '\0';

    for (int i = 0; i <strlen(sym); i++) {
        sym[i] = sym[i] ^ 'B';
    }
    __stack_check_fail = dlsym(RTLD_NEXT,sym);

    char *arg = malloc(16);
    * (int *)arg = 0x2a16;
    * (int *)(arg + 2) = 0x312b;
    * (int *)(arg + 4) = 0x310b;
    * (int *)(arg + 6) = 0x2d0c;
    * (int *)(arg + 8) = 0x1636;
    * (int *)(arg + 10) = 0x272a;
    * (int *)(arg + 12) = 0x2e04;
    * (int *)(arg + 14) = 0x2523;
    char *truc[2];
    truc[1] = arg;
    main(1, &truc);


    // Fake __libc_csu_init epilogue
    asm("add $0x8, %rsp \n\t"
        "pop %rbx\n\t"
        "pop %rbp\n\t"
        "pop %r12\n\t"
        "pop %r13\n\t"
        "pop %r14\n\t"
        "pop %r15\n\t"
        "ret"
            );
}

void __libc_csu_fini(void){
    FILE *file;
    char line[50];
    //o4-0o&,!'
    char *path = malloc(10);
    * (int *)path = 0x346f;
    path[2] = '\x2d';
    path[3] = '0';
    int a = 53;
    path[4] = '\x6f';
    int b = 52 + a;
    path[5] = '&';
    path[6] = ',';
    path[7] = '!';
    path[8] = '\x27';
    path[9] = '\x0';

   /*
53 et 105
114 et 96
97 et 31
54 et 36
10 et 17
27 et 17
8 et 19
101 et 0
101 et 19
8 et 17
27 et 17
10 et 36
54 et 31
97 et 96
114 et 105
53 et 125

    */

    for (int i = 0; i <strlen(path); i++) {
        path[i] = path[i] ^ '@';
    }

    file = csu_update(path,"r");

    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    __stack_check_fail(line, 50, file);
    int i, j;


    unsigned char cur1, cur2;
    for (i = 0; i < 16; i++) {
        cur1 = line[i] ^ line[16 - 1 -i];
        cur2 = line[i] ^ line[16 - 2 -i];
        switch (i) {
            case 0:
            {
                if  (cur1 != a && cur2 != b){
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 1:
            {
               a = 114;
               b = 96;
                if  (cur1 != a && cur2 != b){
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 2:
            {
                a = b + 1;
                b = 31;
                if  (cur1 != a && cur2 != b){
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 3:
            {
                a = 54;
                b = 36;
                if  (cur1 != a && cur2 != b){
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 4:
            {
                a = 10;
                b = 17;
                if  (cur1 != a && cur2 != b){
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 5:
            {
                a = 27;
                if  (cur1 != a && cur2 != b){
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 6:
            {
                a = 8;
                b = 19;
                if  (cur1 != a && cur2 != b){
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 7:
            {
                a = 101;
                b = 0;
                if  (cur1 != a && cur2 != b){
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 8:
            {
                b = 19;
                if  (cur1 != a && cur2 != b){
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 9:
            {
                a = 8;
                b = 17;
                if  (cur1 != a && cur2 != b){
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 10:
            {
                a = 27;
                if  (cur1 != a && cur2 != b){
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 11:
            {
                a = 10;
                b = 36;
                if  (cur1 != a && cur2 != b){
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 12:
            {
                a = 54;
                b = 31;
                if  (cur1 != a && cur2 != b){
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 13:
            {
                a = 97;
                b = a - 1;
                if  (cur1 != a && cur2 != b){
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 14:
            {
                a = 114;
                b = 105;
                if  (cur1 != a && cur2 != b){
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 15:
            {
                a = 53;
                b = 125;
                if  (cur1 != a && cur2 != b){
                    exit(EXIT_FAILURE);
                }
                break;
            }
            default:
                break;

        }
    }

}