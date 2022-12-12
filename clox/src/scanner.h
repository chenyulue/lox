#ifndef _SCANNER_H
#define _SCANNER_H

#include "token.h"

typedef struct {
    int start;
    int current;
    int line;
    char *source;
    int source_length;
    token_list_t *tokens;
} scanner_t;

#endif