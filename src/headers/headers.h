# ifndef HEADERS_H

    # define HEADERS_H

    # include <stdio.h>
    # include <string.h>
    # include <stdlib.h>
    # include <ctype.h>
    # include <stdint.h>
    # include <inttypes.h>

    # define true                ( 1 )
    # define false               ( 0 )

    typedef int8_t i8;      // PRIi8
    typedef int16_t i16;    // PRIi16
    typedef int32_t i32;    // PRIi32
    typedef int64_t i64;    // PRIi64

    typedef uint8_t u8;     // PRIu8
    typedef uint16_t u16;   // PRIu16
    typedef uint32_t u32;   // PRIu32
    typedef uint64_t u64;   // PRIu64

    typedef float f32;      // %f
    typedef double f64;     // %lf

    typedef uint8_t bool;   // %s, PRIbool(bool)
    typedef char *string;   // %s

    # define PRIbool(b)     ( b ? "true" : "false" )

# endif
