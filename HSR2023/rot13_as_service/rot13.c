#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 256

void ignore_me_init_buffering() {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}


void func(){
    static char cmd[8] = "/bin/ls";
    system(cmd);
}

static char hashmap[] = {"NOPQRSTUVWXYZABCDEFGHIJKLM      nopqrstuvwxyzabcdefghijklm"};

char rot13(char character) {
  if (isalpha(character)){
      char c = character - 'A';
      return hashmap[(int)c];
  } else {
    return character;
  }
}

char* srot13(char* str) {
  int length = strlen(str);
  for (int i = 0; i < length; i++) {
    str[i] = rot13(str[i]);
  }
  return str;
}

int main(int argc, char *argv[]){

    ignore_me_init_buffering();
    char buf[MAX];
    
    puts("Welcome to ROT13 as a Service \n ");
    puts("Give me your input: \n");
    fgets(buf, sizeof(buf), stdin);
    puts("Encoding ....");
    srot13(buf);
    printf("Here we are ! The rot13 value of the input is : \n");
    printf(buf);
    exit(EXIT_SUCCESS);
}
