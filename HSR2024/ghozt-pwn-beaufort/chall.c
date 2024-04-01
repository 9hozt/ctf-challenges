#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void ignore_me_init_buffering()
{
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
}


void backdoor(){
  static char cmd[8] = "/bin/ls";
  system(cmd);
}


// Fonction pour coder le texte en clair en utilisant le codage de Beaufort
void beaufortCipher(char *texte, char *cle) {
  int n = strlen(texte);
  int m = strlen(cle);

  for (int i = 0; i < n; i++) {
    if (texte[i] != ' ') {
      int decalage = cle[i % m] - 'A';
      texte[i] = 'Z' - (texte[i] - 'A' - decalage) + 1;
    }
  }
}

int main() {

  ignore_me_init_buffering();

  char texte[100];
  char cle[100];

  printf("Entrez le texte en clair : ");
 fgets(texte, sizeof(texte), stdin);

  printf("Entrez la clé : ");
  fgets(cle, sizeof(cle), stdin);

    beaufortCipher(texte, cle);

    printf("Texte chiffré : %s\n", texte);
    printf("Chiffremnt avec la clef: ");
    printf(cle);

    exit(EXIT_SUCCESS);
  }