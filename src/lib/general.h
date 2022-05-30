# include "../headers/headers.h"
# include "../headers/errcodes.h"

# ifndef GENERAL_H
    
    # define GENERAL_H 1

    # define CHUNK_SIZE ( 8 )

    typedef char chunk[CHUNK_SIZE + 1];

    /**
     * @brief Takes a string and chunks it up into smaller strings of length 8
     *
     * Note that you must free the returned pointer.
     *
     * @param data The string as input
     * @param total_chunks Pointer to total number of chunks, set by this function
     * @return *(chunk[CHUNK_SIZE + 1]) The chunked string
     */
    chunk *gen_chunkup (string data, u64 *total_chunks);

    /**
     * @brief Digests all the chunks together
     *
     * Note that you must free the returned pointer.
     *
     * @param chunks The chunks array
     * @param total_chunks Total number of chunks
     */
    string gen_digest (chunk *chunks, u64 total_chunks);

# endif
