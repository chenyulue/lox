#ifndef _LOX_H
#define _LOX_H

#include <stdio.h>

#define ASSERT_SUCCESS(cond, ...)         \
    {                                     \
        if (!(cond))                      \
        {                                 \
            fprintf(stderr, __VA_ARGS__); \
            return NULL;                  \
        }                                 \
    }                                     \
    while (0)

#endif