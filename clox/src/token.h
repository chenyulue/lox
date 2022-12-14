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

token_t *new_token(token_type type, const char *lexeme, void *literal, int line);
void token_del(token_t *token);
void print_token(token_t *token);
token_list_t *new_token_list(void);
void token_list_add(token_list_t *tokens, token_node_t *token);
void token_list_del(token_list_t *tokens);
token_node_t *new_token_node(token_type type, char *lexeme, void *literal, int line);
void token_node_del(token_node_t *token_node);
char *token_name(token_type type);

#endif