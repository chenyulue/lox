#ifndef _TOKEN_H
#define _TOKEN_H

#include "token_type.h"

typedef struct {
    token_type type;
    char *lexeme;
    void *literal;
    int line;
} token_t;

typedef struct token{
    token_t *token;
    struct token *next;
} token_node_t;

typedef struct {
    token_node_t *head;
    token_node_t *tail;
    size_t size;
} token_list_t;

#endif