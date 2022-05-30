# ifdef TEST

# include "headers/headers.h"
# include "headers/errcodes.h"

# include "lib/general.h"

bool test_general()
{
    bool flag = false;
    string str = "Lorem ipsum dolor sit amet consectetur adipiscing elit sed "
                 "do eiusmod tempor incididunt ut labore et dolore magna aliqua. "
                 "Ut enim ad minim veniam quis nostrud exercitation ullamco laboris "
                 "nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in "
                 "reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla "
                 "pariatur. Excepteur sint occaecat cupidatat non proident sunt in culpa "
                 "qui officia deserunt mollit anim id est laborum.";
    u64 total_chunks = 0;
    chunk *chunks = gen_chunkup (str, &total_chunks);
    string digest = gen_digest (chunks, total_chunks);
    flag = strlen (digest) == CHUNK_SIZE;
    # ifdef DEBUG
         printf ("{\n");
    # endif
    for (u64 i = 0; i < total_chunks; i++) {
        if (strlen (chunks[i]) != CHUNK_SIZE) {
            flag = false;
            break;
        }
        flag = true;
        # ifdef DEBUG
            printf ("    \"%s\",\n", chunks[i]);
        # endif
    }
    # ifdef DEBUG
        printf ("}\n");
        printf ("total_chunks = %" PRIu64 "\n", total_chunks);
        printf ("strlen (str) = %" PRIu64 "\n", strlen (str));
    # endif
    u64 *int_digest = (u64*) (digest);
    printf ("digest: 0x%lx\n", *int_digest);
    free (chunks);
    free (digest);
    return flag;
}

int main (int argsc, string argsv[])
{
    bool test_success = test_general();
    if (!test_success) {
        printf ("Test FAILED\n");
    } else {
        printf ("Test SUCCESS\n");
    }
    return 0;
}

# endif
