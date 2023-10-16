#include <stdio.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include <unistd.h>
#define MAX_LEN 30

void getFlag()
{
  FILE *f;
  char line[50];
  f =  fopen("flag.txt", "r");
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
  char code[MAX_LEN];
  char input[MAX_LEN];
  puts("Generating code: \n");
  int randomData = open("/dev/random", O_RDONLY);
  memset(code,'\x00',MAX_LEN);
  read(randomData,code,MAX_LEN-1);
  puts("Secret code: \n");
  read(0, input,MAX_LEN-1);
  if(!strcmp(input, code))
  {
    getFlag();    
  }
  return EXIT_SUCCESS;

}
