#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"

#define LEN 25
// "HACKVENS{4t4r1P0ngR3tr0!}"

int main(int argc, char *argv[], char *envp[])
{

    if (argc != 2)
    {
        puts("Key missing ! \n");
        return EXIT_FAILURE;
    }
    pingBanner();

    size_t  len;
    unsigned char    *input;
    unsigned char    TTL;

    // Copy argv
    len = strlen(argv[1]);
    input = malloc(len+1);
    memcpy(input, argv[1],len+1);


    if(len != 25){
        printf("Oopsy\n");
        return EXIT_FAILURE;
    }
    if(getenv("TTL"))
    {
        TTL = getTTL();
    }
    else {
        TTL = getLast(input);
    }

    if (!isOdd(TTL))
    {
        printf("Not my turn to play !\n");
        return EXIT_FAILURE;
    }
    else
    {
        unsigned char nextTTL;
        switch (TTL) {
            case 125: {

                if(len != TTL/5)
                {
                    printf("ERROR\n");
                    exit(EXIT_FAILURE);
                }

                nextTTL = ((unsigned char)TTL/5) -1;
                doPing(input,nextTTL);
                bounce("./pong", nextTTL,input);
                break;
            }
            case 23:
            {
                nextTTL = TTL -1;
                doPing(input,nextTTL);
                bounce("./pong", nextTTL,input);
                break;
            }
            case 21:
            {
                nextTTL = TTL -1;
                doPing(input,nextTTL);
                bounce("./pong", nextTTL,input);
                break;
            }
            case 19:
            {
                nextTTL = TTL -1;
                doPing(input,nextTTL);
                bounce("./pong", nextTTL,input);
                break;
            }
            case 17:
            {
                nextTTL = TTL -1;
                doPing(input,nextTTL);
                bounce("./pong", nextTTL,input);
                break;
            }
            case 15:
            {
                nextTTL = TTL -1;
                doPing(input,nextTTL);
                bounce("./pong", nextTTL,input);
                break;
            }
            case 13:
            {
                nextTTL = TTL -1;
                doPing(input,nextTTL);
                bounce("./pong", nextTTL,input);
                break;
            }
            case 11:
            {
                nextTTL = TTL -1;
                doPing(input,nextTTL);
                bounce("./pong", nextTTL,input);
                break;
            }
            case 9:
            {
                nextTTL = TTL -1;
                doPing(input,nextTTL);
                bounce("./pong", nextTTL,input);
                break;
            }
            case 7:
            {
                nextTTL = TTL -1;
                doPing(input,nextTTL);
                bounce("./pong", nextTTL,input);
                break;
            }
            case 5:
            {
                nextTTL = TTL -1;
                doPing(input,nextTTL);
                bounce("./pong", nextTTL,input);
                break;
            }
            case 3:
            {
                nextTTL = TTL -1;
                doPing(input,nextTTL);
                bounce("./pong", nextTTL,input);
                break;
            }
            case 1:
            {
                nextTTL = TTL -1;
                doPing(input,nextTTL);
                unsigned char final[] = {141, 162, 236, 73, 78, 226, 77, 172, 202, 235, 237, 160, 10, 44, 202, 238, 130, 2, 206, 2, 10, 142, 130, 104, 43};
                for(int i = 0; i < 25; i++){
                    if(final[i] != input[i])
                    {
                        printf("You loose!\n");
                        return EXIT_FAILURE;
                    }
                }
                bounce("./pong", nextTTL,input);

                break;
            }

            default:
                break;
        }
    }

    return EXIT_SUCCESS;
}