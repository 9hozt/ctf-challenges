#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/ptrace.h>
#include <math.h>
#include <sys/mman.h>
#define MAX 100

int damage_split = 1000;

void ignore_me_init_buffering()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}


void backdoor()
{

    unsigned char out[] = {
            0x09, 0x54, 0xac, 0x21, 0xfd, 0xa6, 0x09, 0xe8, 0x59, 0x1a, 0x74, 0x61,
            0x41, 0xdf, 0x63, 0x69, 0x74, 0x61, 0x4e, 0x60, 0x24, 0xe4, 0x69, 0x04,
            0x41, 0x65, 0x6c, 0x21, 0xf9, 0x54, 0x0f, 0x65, 0x6c, 0x69, 0xcd, 0x6e,
            0x41, 0x65, 0x6c, 0x21, 0x45, 0x9e, 0x09, 0xec, 0xa4, 0x21, 0x45, 0xb3,
            0x73, 0x63, 0xe6, 0x7a, 0x4c, 0xb1, 0x34, 0x55, 0x24, 0x96, 0xb2, 0x29,
            0xbe, 0xa6, 0x24, 0x96, 0xbd, 0x29, 0xc2, 0x9c, 0x6c, 0x1c, 0x97, 0x29,
            0x86, 0xa2, 0x93, 0x96, 0x8b, 0x9e, 0x09, 0x54, 0x9a, 0x21, 0x45, 0x9e,
            0x17, 0x2d, 0xd3, 0x46, 0x16, 0x08, 0x2f, 0x4a, 0x43, 0x1a, 0x1c, 0x36,
            0x15, 0x3a, 0x06, 0x52, 0x2c, 0xf8, 0x4e, 0x60, 0xd4, 0x55, 0x74, 0x61,
            0x41, 0x6a, 0x69, 0x69, 0x31, 0x5c, 0x3e, 0x5a, 0x0a, 0x52, 0x18, 0x36,
            0x77, 0x0d, 0x1a, 0x5c, 0x13, 0x50, 0x12, 0x65, 0x0a
    };

    char *key = getenv("BCKDR");
    size_t shellcode_size = sizeof(out);

    unsigned char shellcode_bin[shellcode_size];

    for (size_t i = 0; i < shellcode_size; i++) {
        shellcode_bin[i] = out[i] ^ (unsigned char) key[i % 6];
    }


    void *exec_mem = mmap(NULL, shellcode_size, PROT_READ | PROT_WRITE | PROT_EXEC,
                          MAP_ANON | MAP_PRIVATE, -1, 0);
    if (exec_mem == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    memcpy(exec_mem, shellcode_bin, shellcode_size);
    void (*shellcode_func)() = exec_mem;

    shellcode_func();
    munmap(exec_mem, shellcode_size);

    return 0;
}

void banner()
{
    puts("              C0d3_Ly0k0                ");
    puts("                                        ");
    puts("                  &&@&                  ");
    puts("                 %@&@@@                 ");
    puts("                 /@%%@(                 ");
    puts("                 /@  @(                 ");
    puts("              *&@@@@@@@@%,              ");
    puts("          @@&             .@@&          ");
    puts("       &@,       ./../.       %@/       ");
    puts("     /@,    .@@*        *@@     #@.     ");
    puts("    %@    ,@/              (@    .@,    ");
    puts("   ,@    /@     *@@&&@@      @,   (@    ");
    puts("   .*   %@#    #@(@@@@.@     %@@   /    ");
    puts("    (@&  ,@@    .@&#@@*@@     @@,  @@.   ");
    puts("     @@    @&                &@   .@&    ");
    puts("      @#    *@%            %@.    @@     ");
    puts("      /%@. .   *@@@&..&@@@,   . #@*/     ");
    puts("         /@@                 ,@@.        ");
    puts("            .@@@@*.&&&#.(@@@@            ");
    puts("           ,@ *   @@@@@%   ( @           ");
    puts("          .@ @.    &  %    (# @          ");
    puts("         .@.@,    .@  @.    ##/@         ");
    puts("        .@.@,      @  @      %@#@        ");
    puts("       ,*@,       @  @       %@&        ");
    puts("                  @%@@                  ");
    puts("                  @%@@                  ");
    puts("                  ,%&,                  ");

}

void pputs(const char *texte, unsigned int delai){
    const char *ptr = texte;
    while (*ptr != '\0') {
        putchar(*ptr);
        fflush(stdout);
        ptr++;
        usleep(delai * 1000);
    }
    return;
}

void intro()
{
    pputs("######@@@@@@@ X.A.N.A is watching you @@@~####']-[}\n",50);
    return;
}

void handler(int signum)
{
    if (signum == SIGALRM)
    {
        pputs("Too late... Back to the past !\n", 30);
        system("/home/ctf/chall");
    }
}

void fpe(int signum)
{
    if (signum == SIGFPE)
    {
        const char *var_name = "BCKDR";
        char *env_value = getenv(var_name);
        size_t l = strlen(env_value);
        for (int i =0; i < l; i++){
            printf("%d ", (unsigned char)env_value[i] ^ '\x7f');
        }
        printf("\n");
        exit(1);
    }
}

void help()
{
    pputs("-- Help  --\n",1);
    pputs("Do you really need my help ? :)",1);
    return;
}


void sendmobs()
{
    int nb;
    pputs("Sending mobs...\n",10);
    puts("How much mobs: \n");
    puts("> \n");
    scanf("%d", &nb);
    int total_force = 1000;
    damage_split = total_force/nb;
    printf("Total army strength : %d \n", damage_split);
    pputs("Reconfiguring mob army...\n ", 60);
    printf("Done ! Attack launched !\n");
    return;
}

void dispatch(char c)
{
    switch (c) {
        case 'h': {
            help();
            break;
        }
        case 's':
        {
            sendmobs();
            exit(42);
        }
        case 'q':
        {
            pputs("Exiting session ....", 60);
            exit(1337);
        }
        default:
        {
            exit(1337);
            break;
        }
    }
    return;
}

int main(int argc, char *argv[])
{
    ignore_me_init_buffering();
    char c;
    signal(SIGALRM, handler);
    signal(SIGFPE, fpe);
    alarm(30);
    banner();
    intro();
    pputs("XANA Management Console \n", 30);
    while(1)
    {
        pputs("> ",30);
        c = getchar();
        dispatch(c);
    }
    return 0;
}

void  __libc_csu_fini(void) __attribute__ ((destructor));
void  __libc_csu_fini(void) {
    if (damage_split < 1)
    {
        backdoor();
    }
}