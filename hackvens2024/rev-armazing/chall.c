#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 256

unsigned int step;

unsigned int base[42] = {
    0xA1B2C3D4, 0x5F6E7D8C, 0x9A0B1C2D, 0x3E4F5A6B, 0x12345678, 0x90ABCDEF,
    0xFEDCBA09, 0x2468ACE0, 0x13579BDF, 0xAABBCCDD, 0x11223344, 0x55667788,
    0x99AABBCC, 0xFFEEDDCC, 0x22334455, 0x66778899, 0xDEADBEEF, 0xB16B00B5,
    0xCAFEBABE, 0x8BADF00D, 0x0BADC0DE, 0xABCDEF01, 0xAC1D3B07, 0x50607080,
    0x1A2B3C4D, 0x5E6F7A8B, 0x9B0C1D2E, 0x3F4E5D6C, 0xABAD1D3A, 0x34567890,
    0x98765432, 0xFEDC1234, 0x456789AB, 0xCDEF0123, 0x89ABCDEF, 0x01234567,
    0x89ABCDEF, 0x12345678, 0x76543210, 0xFEDCBA98, 0xDECAFBAD, 0xBEEFCAFE
};


unsigned int target[] = {
    3990705690,
    3237526486,
    1798528091,
    763966678,
    513164626,
    2989230759,
    3519808802,
    3154852637,
    2969865278,
    3221947047,
    728904616,
    242236652,
    3923475827,
    4121602817,
    1882559716,
    312628894
};

char *flag = "\x29\xdb\xf3\xf4\xd3\x95\xb1\x64\xe2\x6b\x40\xe8\x8d\x45\xe4\xe6"
             "\xf1\x4f\xd6\xd4\x25\xc1\xfb\x52\x70\x06\xc8\xe2\xf0\x36\xe0\xd9";

void swap(unsigned char *a, unsigned char *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int KSA(char *key, unsigned char *S) {
    const size_t len = strlen(key);
    int j = 0;

    for(int i = 0; i < N; i++)
        S[i] = i;

    for(int i = 0; i < N; i++) {
        j = (j + S[i] + key[i % len]) % N;
        swap(&S[i], &S[j]);
    }

    return 0;
}

int PRGA(unsigned char *S, char *plaintext, unsigned char *ciphertext) {

    int i = 0;
    int j = 0;

    for(size_t n = 0, len = strlen(plaintext); n < len; n++) {
        i = (i + 1) % N;
        j = (j + S[i]) % N;

        swap(&S[i], &S[j]);
        int rnd = S[(S[i] + S[j]) % N];

        ciphertext[n] = rnd ^ plaintext[n];

    }

    return 0;
}

int RC4(char *key, char *plaintext, unsigned char *ciphertext) {

    unsigned char S[N];
    KSA(key, S);

    PRGA(S, plaintext, ciphertext);

    return 0;
}


// #pragma GCC push_options
// #pragma GCC optimize ("O0")
unsigned int craftConst() {
    unsigned int res;
    unsigned int c1 = base[step+15];
    unsigned int c2 = base[(step+10)*2];
    unsigned int c3 = base[(56%3)+step*26];
    unsigned int c4 = 0x34a51bf2;

    if(step) {
        res = c1 ^ c2 ^ c3 ^ c4;
    }
    else {
        res = c1 ^ c2;
    }
    step = 0;
    return res;
}
// #pragma GCC pop_options

unsigned int crc32b(unsigned char *message) {
    int i, j;
    unsigned int byte, crc, mask;
    step++;
    unsigned int magic = craftConst();

    i = 0;
    crc = 0xFFFFFFFF;
    while (message[i] != 0) {
        byte = message[i];
        crc = crc ^ byte;
        for (j = 7; j >= 0; j--) {
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (magic & mask);
        }
        i = i + 1;
    }
    return ~crc;
}

void banner() {

}


// HACKVENS{CrC32_1nt0_rC4_@aRch64}
// 7$FqR#5wdx!LnPz8&mT9Uj@3XkH^Vo2r

/*
*b'7$' => 3990705690
b'Fq' => 3237526486
b'R#' => 1798528091
b'5w' => 763966678
b'dx' => 513164626
b'!L' => 2989230759
b'nP' => 3519808802
b'z8' => 3154852637
b'&m' => 2969865278
b'T9' => 3221947047
b'Uj' => 728904616
b'@3' => 242236652
b'Xk' => 3923475827
b'H^' => 4121602817
b'Vo' => 1882559716
b'2r' => 312628894
 *
 */

int main(int argc, char *argv[]) {


    if (argc != 2) {
        printf("Usage: %s password\n", argv[0]);
        exit(1);
    }

    int length = strlen(argv[1]);
    if (length != 32) {
        printf("Invalid password\n");
        exit(1);
    }

    char current[3];
    unsigned int crc;
    unsigned int res = 0;
    for (int i = 0; i < length; i += 2) {
        strncpy(current, &argv[1][i], 2);
        current[2] = '\0';
        crc = crc32b(current);
        if(crc == target[i/2]) {
           res++;
        }
        // printf("Current %d: %s => %u\n",res, current, crc);
    }

    if (res == 16) {
        printf("Password verification successful\n");
        printf("Decrypting flag...\n");
        unsigned char *plain_flag = malloc(sizeof(int) *  strlen(flag));
        RC4(argv[1], flag, plain_flag);
        printf("%s\n", plain_flag);
    }
    else {
        printf("Invalid Password ...\n");
        exit(1);
    }

    return 0;
}

