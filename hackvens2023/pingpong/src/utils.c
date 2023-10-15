//
// Created by ghozt on 27/09/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "utils.h"


void rotateString(unsigned char *str, int n) {
    int l = 25;

    char temp[26];
    memcpy(temp+25-n, str, n);
    memcpy(temp, str +n , 25-n);
    memcpy(str , temp, 25);
}



void rotateAgainString(unsigned char *str)
{
    char temp[26];
    memcpy(temp, str+13,25-13);
    memcpy(temp+25-13, str +5 , 13-5);
    memcpy(temp +25-5, str, 5);
    memcpy(str,temp,25);
}


void transfo(unsigned char * str, unsigned char r)
{
    unsigned char c;
    for (int i = 0; i <25; i++) {
        c = ((str[i] >> r) + ((str[i]  & ((1 << r) -1)) << (8-r)));
        str[i] = c;
    }

}

void doPing(unsigned char *str, unsigned char TTL)
{
    xorStringWithChar(str,TTL);
    transfo(str,3);
    rotateString(str,5);
    //printf("#########PING TTL %d\n", TTL);
    //printf("[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d]\n",str[ 0 ],str[ 1 ],str[ 2 ],str[ 3 ],str[ 4 ],str[ 5 ],str[ 6 ],str[ 7 ],str[ 8 ],str[ 9 ],str[ 10 ],str[ 11 ],str[ 12 ],str[ 13 ],str[ 14 ],str[ 15 ],str[ 16 ],str[ 17 ],str[ 18 ],str[ 19 ],str[ 20 ],str[ 21 ],str[ 22 ],str[ 23 ],str[ 24 ]);

}

void doPong(unsigned char *str, unsigned char TTL)
{
    xorStringWithChar(str,TTL);
    transfo(str,7);
    xorStringWithChar(str,6);
    rotateAgainString(str);
    //printf("#########PONG TTL %d\n", TTL);
    //printf("[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d]\n",str[ 0 ],str[ 1 ],str[ 2 ],str[ 3 ],str[ 4 ],str[ 5 ],str[ 6 ],str[ 7 ],str[ 8 ],str[ 9 ],str[ 10 ],str[ 11 ],str[ 12 ],str[ 13 ],str[ 14 ],str[ 15 ],str[ 16 ],str[ 17 ],str[ 18 ],str[ 19 ],str[ 20 ],str[ 21 ],str[ 22 ],str[ 23 ],str[ 24 ]);
}

unsigned int getTTL()
{
    unsigned char *TTLenv = (unsigned char *)  getenv("TTL");
    return (unsigned int) *TTLenv;
}

void xorStringWithChar(char *str, char c) {
    for (int i = 0; i <25; i++) {
        str[i] = str[i] ^ c;
    }
}

char *forgeTTL(unsigned char TTL)
{
    char *TTLenv = malloc(6*sizeof(char));
    if (TTLenv == NULL)
    {
        perror("malloc failure");
        exit(EXIT_FAILURE);
    }
    snprintf(TTLenv,6,"TTL=%c",TTL);
    return TTLenv;
}


void bounce(char *dest, unsigned char TTL, unsigned char *input)
{
    char *newargv[] = {dest, input, NULL};
    char *newenvp[] =
            {
                    forgeTTL(TTL),
            };
    execve(dest, newargv, newenvp);
    perror("BOUNCE ERROR");
}

int isEven(int i)
{
    if (i % 2 == 0) {
        return 1;
    } else {
        return 0;
    }
}

int isOdd(int i)
{
    if (i % 2 == 0) {
        return 0;
    } else {
        return 1;
    }
}

unsigned char getLast(char *string)
{
    ssize_t l = strlen(string);
    return string[l-1];
}

void pingBanner()
{
puts(" _______  ___   __    _  _______");
puts("|       ||   | |  |  | ||       |");
puts("|    _  ||   | |   |_| ||    ___|");
puts("|   |_| ||   | |       ||   | __");
puts("|    ___||   | |  _    ||   ||  |");
puts("|   |    |   | | | |   ||   |_| |");
puts("|___|    |___| |_|  |__||_______|\n");
}


void pongBanner()
{
   puts(" _______  _______  __    _  _______");
   puts("|       ||       ||  |  | ||       |");
   puts("|    _  ||   _   ||   |_| ||    ___|");
   puts("|   |_| ||  | |  ||       ||   | __");
   puts("|    ___||  |_|  ||  _    ||   ||  |");
   puts("|   |    |       || | |   ||   |_| |");
   puts("|___|    |_______||_|  |__||_______|\n");
}