#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX(a, b) ( a > b ? a : b )
#define MIN(a, b) ( a < b ? a : b )

typedef unsigned char ubyte_t;

typedef struct
{
    ubyte_t *data;
    size_t size;
} Bytes;

Bytes input_bytes(FILE *fd)
{
    if (!fd) abort();
    size_t size = 0;
    char *data = NULL;
    do {
        char ch = fgetc(fd);
        if ((signed char) ch == EOF) break;
        data = realloc(data, ++size);
        if (!data) abort();
        data[size-1] = ch;
    } while (true);
    Bytes bytes = { (ubyte_t *) data, size };
    return bytes;
}

char to_hex(ubyte_t bits4)
{
    bits4 = bits4 & 0x0f;
    if (bits4 >= 0x00 && bits4 <= 0x09) return bits4 + '0';
    else if (bits4 >= 0x0a && bits4 <= 0x0f) return bits4 - 0x0a + 'a';
    else abort();
}

char *to_hex_string(Bytes bytes)
{
    if (!bytes.data) abort();
    size_t size = 2 * bytes.size +1;
    char *s = malloc(size);
    for (size_t i = 0, j = 0; i < bytes.size; i++, j += 2) {
        ubyte_t byte = bytes.data[i];
        s[j] = to_hex(byte >> 4);
        s[j+1] = to_hex(byte);
    }
    s[size-1] = 0;
    return s;
}

Bytes x_hash(Bytes bytes)
{
    if (!bytes.data) abort();
    /* DEF0: follows pattern of DEF1 with a digit b/w each term
     * DEF1: A-Z with alternating case
     */
    const char DEF0[33] = "0qQ1rR2sS3tT4uU5vV6wW7xX8y9YzZaA";
    const char DEF1[33] = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpP";
    const size_t DEF_LEN = 33;
    Bytes hash = { malloc(DEF_LEN -1), DEF_LEN -1 };
    const size_t repeats = MIN(hash.size, bytes.size);
    const size_t updates = MAX(hash.size, bytes.size);
    for (int i = 0, j = 0; i < updates; i++, j += DEF_LEN/2)
        hash.data[i] = bytes.data[j % bytes.size] % hash.size ?
            DEF0[j % DEF_LEN] : DEF1[j % DEF_LEN];
    for (int i = hash.size/2, j = 0; i < updates; i += DEF_LEN/2, j += 8)
        hash.data[i] += bytes.data[j % bytes.size];
    for (int i = 0; i < repeats; i++)
        for (int j = 0; j < updates; j++)
            hash.data[j % hash.size] += bytes.data[j % bytes.size];
    return hash;
}

void printhelp()
{
    printf(
        "USAGE: xhash [path]\n"
        "  -h --help   Display this message\n"
    );
}

int main(int argc, char *argv[])
{
    if (argc > 2) {
        fprintf(stderr, "xhash: too many arguments\n");
        printhelp();
        exit(2);
    }
    char *arg = argc < 2 ? "-" : argv[1];
    if (!strcmp(arg, "-")) {
        Bytes bytes = input_bytes(stdin);
        Bytes hash = x_hash(bytes);
        char *hex = to_hex_string(hash);
        printf("%s\n", hex);
        free(bytes.data);
        free(hash.data);
        free(hex);
    } else if (!strcmp(arg, "--help") || !strcmp(arg, "-h")) {
        printhelp();
    } else if (arg[0] == '-') {
        fprintf(stderr, "xhash: invalid argument\n");
        printhelp();
        exit(4);
    } else {
        FILE *fd = fopen(arg, "rb");
        if (!fd) {
            fprintf(stderr, "xhash: cannot access '%s'\n", arg);
            exit(5);
        }
        Bytes bytes = input_bytes(fd);
        Bytes hash = x_hash(bytes);
        char *hex = to_hex_string(hash);
        printf("%s\n", hex);
        free(bytes.data);
        free(hash.data);
        free(hex);
        fclose(fd);
    }
    return 0;
}
