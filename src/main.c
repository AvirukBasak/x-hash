# include "headers/headers.h"
# include "headers/errcodes.h"

# include "lib/general.h"

int main (int argsc, char **argsv)
{
    string data = NULL;
    u64 datalen = 0;
    if (argsc < 2) {
        i8 c;
        while ((c = getchar()) != 0 && c != EOF && c != 13 && c != 10) {
            data = realloc (data, sizeof (char) * ++datalen);
            data[datalen - 1] = c;
        }
        data = realloc (data, sizeof (char) * datalen + 1);
        data[datalen] = 0;
    } else {
        for (u64 i = 1; i < argsc; i++) {
            datalen += strlen (argsv[i]) + 1;
        }
        data = calloc (datalen, sizeof (char));
        data[0] = 0;
        for (u64 i = 1; i < argsc; i++) {
            strcat (data, argsv[i]);
            strcat (data, " ");
        }
        data[datalen -1] = 0;
    }
    # ifdef ECHO
        printf ("%s\n", data);
        printf ("datalen: %"PRIu64 "\n", datalen);
    # endif
    u64 total_chunks;
    chunk *chunks_arr = gen_chunkup (data, &total_chunks);
    string digest = gen_digest (chunks_arr, total_chunks);
    # ifdef DEBUG
        printf ("%s\n", digest);
        printf ("total_chunks: %" PRIu64 "\n", total_chunks);
    # else
        u64 int_digest = *((u64*)digest);
        printf ("0x%lx\n", int_digest);
    # endif
    free (data);
    free (chunks_arr);
    free (digest);
    return 0;
}
