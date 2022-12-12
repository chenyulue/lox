#ifndef _LOX_H
#define _LOX_H

#include <stdio.h>

#define ASSERT_SUCCESS(cond, ...)         \
    {                                     \
        if (!(cond))                      \
        {                                 \
            fprintf(stderr, __VA_ARGS__); \
            return 1;                    \
        }                                 \
    }                                     \
    while (0)

#endif