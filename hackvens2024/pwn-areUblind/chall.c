#include <stdio.h>
#include <stdlib.h>

char *fmt[] ={"Are you blind? Format your eyes, Can't you see the %s ?\n",
    "Es-tu aveugle ? Formate tes yeux ! Ne peux-tu pas voir le %s ?\n",
    "¿Estás ciego? ¡Formatea tus ojos! ¿No puedes ver el %s?\n",
    "Bist du blind? Formatiere deine Augen! Kannst du das %s nicht sehen?\n",
    "Sei cieco? Formatta i tuoi occhi! Non riesci a vedere il %s?\n",
    "Está cego? Formate seus olhos! Não consegue ver o %s?\n",
    "Ben je blind? Formatteer je ogen! Kun je de %s niet zien?\n",
    "Ты слепой? Переформатируй глаза! Разве ты не видишь %s?\n"};

#define MAX 8

typedef struct {
    char buffer[256];
    char *format;
} display;

display d;
char format[256];

void main() {
    int i,j;
    setvbuf(stdout, 0LL, 2, 0LL);
    setvbuf(stdin, 0LL, 2, 0LL);
    while(1) {
        int i = rand() % MAX;
        for (j=0;fmt[i][j];j++) format[j]=fmt[i][j];
        format[j]=0;
        d.format=format;
        scanf("%256s",d.buffer); // OBO
        printf(d.format,d.buffer); // Controlled format with OBO
    }
}