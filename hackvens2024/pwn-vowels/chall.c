#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


void bd(){
    static char cmd[8] = "/bin/XX";
    system(cmd);
}

void ignore_me_init_buffering() {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

int count_v(const char *input) {
    int ctr = 0;
    while (*input) {
        char c = tolower(*input); 
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y') {
            ctr++;
        }
        input++;
    }
    return ctr;
}

int display(const char *input, int ctr){
    printf("Your string ");
    printf(input);
    printf(" has %d vowels\n", ctr);
}

int main() {
    ignore_me_init_buffering();
    int  ctr;
    char input[256];

    printf("Enter string : ");
    fgets(input, sizeof(input), stdin);

    ctr = count_v(input);
    display(input, ctr);
    exit(0);
}