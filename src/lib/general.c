# include "general.h"

/**
 * @brief Takes a string and chunks it up into smaller strings of length 8
 *
 * Note that you must free the returned pointer.
 *
 * @param data The string as input
 * @param total_chunks Pointer to total number of chunks, set by this function
 * @return *(chunk[CHUNK_SIZE + 1]) The chunked string
 */
chunk *gen_chunkup (string data, u64 *total_chunks)
{
    u64 len = strlen (data);
    i8 unfilled_bytes = CHUNK_SIZE - len % CHUNK_SIZE;
    *total_chunks = 2 * (len / CHUNK_SIZE + (unfilled_bytes ? 1 : 0));
    chunk *arr_chunks = malloc (*total_chunks * sizeof (char[CHUNK_SIZE + 1]));
    for (u64 i = 0, j = 0; i < *total_chunks; i++) {
        for (u64 k = 0; k < CHUNK_SIZE; j++, k++) {
            if (j == len)
                j = 0;
            arr_chunks[i][k] = data[j];
        }
        arr_chunks[i][CHUNK_SIZE] = 0;
    }
    return arr_chunks;
}
