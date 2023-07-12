/*
 *
 *  Build with:  gcc -Wall -Wextra -Werror -no-pie png_analyzer.c
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <endian.h>
#include <sys/stat.h>

#define CHUNKMAXSZ 8192
#define ITEXT 0x74584574

typedef struct  s_chunk
{
    uint32_t        size;
    uint32_t        type;
    uint32_t        crc;
    uint8_t         data[CHUNKMAXSZ];
    void            (*callback)(uint8_t *);
    struct s_chunk  *next;
}               t_chunk;

void    do_nothing(uint8_t *input)
{
    (void)input;
}

size_t  parse_chunk(uint8_t *data, t_chunk **chunk)
{
    if (!(*chunk = (t_chunk *)malloc(sizeof(t_chunk))))
    {
        printf("[!] malloc failed: %s (seem funky baby)\n", strerror(errno));
        exit(1);
    }
    memset(*chunk, 0, sizeof(t_chunk));
    (*chunk)->size = be32toh(*(uint32_t *)data);
    (*chunk)->type = *(uint32_t *)(data + sizeof(uint32_t));
    (*chunk)->crc = be32toh(*(uint32_t *)(data + (2 * sizeof(uint32_t)) + (*chunk)->size));
    (*chunk)->callback = (void (*)(uint8_t *))do_nothing;
    memcpy((uint8_t *)(*chunk)->data, data + (2 * sizeof(uint32_t)), (*chunk)->size);
    return ((3 * sizeof(uint32_t)) + (*chunk)->size);
}

t_chunk *parse_png(uint8_t *data, size_t size)
{
    size_t      n = 0;
    uint64_t    hdr = -1;
    t_chunk     *chunk = NULL;
    t_chunk     *bk = NULL;
    t_chunk     *tmp = NULL;

    hdr = *(uint64_t *)data;
    data += sizeof(uint64_t);
    size -= sizeof(uint64_t);
    if (hdr != 0xa1a0a0d474e5089)
    {
        printf("[!] This is not a PNG image. Supply a real png.\n");
        exit(1);
    }
    while (size > 0)
    {
        n = parse_chunk(data, &chunk);
        data += n;
        size -= n;
        if (chunk->type != ITEXT)
        {
            free(chunk);
            continue ;
        }
        if (!(bk))
        {
            bk = chunk;
            tmp = chunk;
        }
        else
        {
            tmp->next = chunk;
            tmp = tmp->next;
        }
    }
    return (bk); 
}

void    analyze(t_chunk *list)
{
    size_t  n = 0;
    t_chunk *tmp;

    tmp = list;
    while (tmp)
    {
        printf("[+] Chunk %ld:\n<br />", n);
        printf("\t- Type: %.4s\n<br />", (char *)&tmp->type);
        printf("\t- Size: %d\n<br />", tmp->size);
        printf("\t- CRC: 0x%08x\n<br /><br />", tmp->crc);
        tmp->callback(tmp->data);
        tmp = tmp->next;
        n++;
    }
}

int     main(int argc, char **argv)
{
    int         fd = -1;
    void        *img = NULL;
    t_chunk     *list;
    struct stat statbuf;

    if (argc != 2)
        return 1;
    system("echo $(date) - File analyzed from /var/www/dev/png_analyzer >> /var/www/dev/logs/log");
    memset(&statbuf, 0, sizeof(struct stat));
    if (stat(argv[1], &statbuf) < 0)
    {
        printf("[!] Stat error on %s: %s\n", argv[1], strerror(errno));
        return (1);
    }
    if ((fd = open(argv[1], O_RDONLY)) < 0)
    {
        printf("[!] Cannot open %s: %s\n", argv[1], strerror(errno));
        return (1);
    }
    if (!(img = malloc(statbuf.st_size)))
    {
        printf("[+] Malloc failure, funky: %s\n", strerror(errno));
        return (1);
    }
    read(fd, img, statbuf.st_size);
    close(fd);
    list = parse_png((uint8_t *)img, statbuf.st_size);
    analyze(list);
    free(img);
    return (0);
}
