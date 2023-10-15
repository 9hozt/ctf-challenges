//
// Created by ghozt on 27/09/23.
//

#ifndef GNOPGNIP_UTILS_H
#define GNOPGNIP_UTILS_H

void rotateString(unsigned char *str, int n);
void rotateAgainString(unsigned char *str);
void transfo(unsigned char *str, unsigned char r);
void doPing(unsigned char *str, unsigned char TTL);
void doPong(unsigned char *str, unsigned char TTL);
void pingBanner();
void pongBanner();
unsigned char getLast(char *string);
int isEven(int i);
int isOdd(int i);
char *forgeTTL(unsigned char TTL);
void xorStringWithChar(char *str, char c);
unsigned int getTTL();
void bounce(char *dest, unsigned char TTL, unsigned char *input);
#endif //GNOPGNIP_UTILS_H
