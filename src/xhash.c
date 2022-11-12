#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
    const char DEF0[33] = { 0 };
    const char DEF1[33] = { 0 };
    const size_t DEF_LEN = 32;
    Bytes hash = { malloc(DEF_LEN), DEF_LEN -1 };
    return hash;
}

void printhelp()
{
    printf(
        "USAGE: xhash [option] [args]\n"
        "  -h --help   Display this message\n"
        "  -f --file   Hash a file\n"
    );
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "xhash: too few arguments\n");
        printhelp();
        exit(1);
    } else if (argc > 3) {
        fprintf(stderr, "xhash: too many arguments\n");
        exit(2);
    }
    char *arg = argv[1];
    if (strcmp(arg, "--help") == 0
        || strcmp(arg, "-h") == 0) printhelp();
    else if (!strcmp(arg, "-")) {
        Bytes bytes = input_bytes(stdin);
        Bytes hash = x_hash(bytes);
        char *hex = to_hex_string(hash);
        printf("%s\n", hex);
        free(bytes.data);
        free(hash.data);
        free(hex);
        return 0;
    } else if (strcmp(arg, "--file") == 0
        || strcmp(arg, "-f") == 0) {
        if (argc < 2) {
            fprintf(stderr, "xhash: file path not provided\n");
            exit(3);
        }
        FILE *fd = fopen(argv[2], "rb");
        if (!fd) {
            fprintf(stderr, "xhash: cannot access '%s'\n", argv[2]);
            exit(4);
        }
        Bytes bytes = input_bytes(fd);
        Bytes hash = x_hash(bytes);
        char *hex = to_hex_string(hash);
        printf("%s\n", hex);
        free(bytes.data);
        free(hash.data);
        free(hex);
        fclose(fd);
        return 0;
    } else {
        fprintf(stderr, "xhash: invalid argument\n");
        printhelp();
        exit(5);
    }
    return 0;
}
