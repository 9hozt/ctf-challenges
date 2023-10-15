#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"


int main(int argc, char *argv[], char *envp[])
{
    if (argc != 2)
    {
        puts("Key missing");
        return EXIT_FAILURE;
    }

    pongBanner();
    unsigned char TTL = getTTL();
    unsigned char nextTTL;
    if (!isEven(TTL))
    {
        printf("Not my turn to play !\n");
        return EXIT_FAILURE;
    }
    char *input;
    ssize_t len;

    len = strlen(argv[1]);
    input = malloc(len+1);
    memcpy(input, argv[1],len+1);

    if(len != 25){
        printf("Oopsy\n");
        return EXIT_FAILURE;
    }

    switch (TTL) {
        case 24:{
            nextTTL = TTL -1;
            doPong(input,nextTTL);
            bounce("./ping",nextTTL,input);
            break;
        }
        case 22:{
            nextTTL = TTL -1;
            doPong(input,nextTTL);
            bounce("./ping",nextTTL,input);
            break;
        }
        case 20:{
            nextTTL = TTL -1;
            doPong(input,nextTTL);
            bounce("./ping",nextTTL,input);
            break;
        }
        case 18:{
            nextTTL = TTL -1;
            doPong(input,nextTTL);
            bounce("./ping",nextTTL,input);
            break;
        }
        case 16:{
            nextTTL = TTL -1;
            doPong(input,nextTTL);
            bounce("./ping",nextTTL,input);
            break;
        }
        case 14:{
            nextTTL = TTL -1;
            doPong(input,nextTTL);
            bounce("./ping",nextTTL,input);
            break;
        }
        case 12:{
            nextTTL = TTL -1;
            doPong(input,nextTTL);
            bounce("./ping",nextTTL,input);
            break;
        }
        case 10:{
            nextTTL = TTL -1;
            doPong(input,nextTTL);
            bounce("./ping",nextTTL,input);
            break;
        }
        case 8:{
            nextTTL = TTL -1;
            doPong(input,nextTTL);
            bounce("./ping",nextTTL,input);
            break;
        }
        case 6:{
            nextTTL = TTL -1;
            doPong(input,nextTTL);
            bounce("./ping",nextTTL,input);
            break;
        }
        case 4:{
            nextTTL = TTL -1;
            doPong(input,nextTTL);
            bounce("./ping",nextTTL,input);
            break;
        }
        case 2:{
            nextTTL = TTL -1;
            doPong(input,nextTTL);
            bounce("./ping",nextTTL,input);
            break;
        }
        case 0:{
            printf("YOU WIN THE MATCH\n");
            break;
        }
        default:
            break;
    }

    return EXIT_SUCCESS;
}