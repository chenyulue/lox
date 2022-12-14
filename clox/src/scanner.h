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
    token_type keywords[16];
} scanner_t;

scanner_t *new_scanner(char *source);
void scanner_del(scanner_t *scanner);
token_list_t *scan_tokens(scanner_t *scanner);
void scan_token(scanner_t *scanner);
void identifier(scanner_t *scanner);
void number(scanner_t *scanner);
void string(scanner_t *scanner);
int match(scanner_t *scanner, char expected);
char peek(scanner_t *scanner);
char peek_next(scanner_t *scanner);
int is_alpha(char c);
int is_alpha_numeric(char c);
int is_at_end(scanner_t *scanner);
char advance(scanner_t *scanner);
void add_token(scanner_t *scanner, token_type type,  void *literal);
char *substring(char *source, int start, int end);

#endif