# include "headers/headers.h"
# include "headers/errcodes.h"

# include "lib/globals.h"
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
    string data = malloc (datalen * sizeof (char));
    data[0] = 0;
    for (u64 i = 1; i < argsc; i++) {
        strcat (data, argsv[i]);
        strcat (data, " ");
    }
    # ifdef ECHO
        printf ("%s\n", data);
    # endif
    free (data);
    return 0;
}
