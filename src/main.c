# include "headers/headers.h"
# include "headers/errcodes.h"

# include "lib/general.h"

int main (int argsc, char **argsv)
{
    if (argsc < 2) {
        fprintf (stderr, "xhash: error: no arguments provided\n");
        exit (E_CLIARGS);
    }
    u64 datalen = 0;
    for (u64 i = 1; i < argsc; i++) {
        datalen += strlen (argsv[i]) + 1;
    }
    string data = calloc (datalen, sizeof (char));
    data[0] = 0;
    for (u64 i = 1; i < argsc; i++) {
        strcat (data, argsv[i]);
        strcat (data, " ");
    }
    # ifdef ECHO
        printf ("%s\n", data);
    # endif
    u64 total_chunks;
    string digest = gen_digest (gen_chunkup (data, &total_chunks), total_chunks);
    # ifdef DEBUG
        printf ("%s\n", digest);
    # else
        u64 int_digest = *((u64*)digest);
        printf ("0x%lx\n", int_digest);
    # endif
    free (data);
    free (digest);
    return 0;
}
