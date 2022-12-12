#include <stdlib.h>
#include <string.h>

#include "scanner.h"
#include "token.h"

scanner_t *new_scanner(char *source)
{
    scanner_t *a_scanner = malloc(sizeof(scanner_t));
    a_scanner->source = source;
    token_list_t *tokens = new_token_list();
    a_scanner->tokens = tokens;

    a_scanner->start = 0;
    a_scanner->current = 0;
    a_scanner->line = 0;

    a_scanner->source_length = strlen(source);

    return a_scanner;
}

scanner_t *scan_tokens(scanner_t *scanner)
{
    while (!is_at_end(scanner))
    {
        scanner->start = scanner->current;
        scan_token(scanner);
    }

    token_node_t *a_new_token_node = new_token_node(END_OF_FILE, "", NULL, scanner->line);
    token_list_add(scanner->tokens, a_new_token_node);

    return scanner;
}

void scan_token(scanner_t *scanner)
{
    char c = advance(scanner);
    
    switch(c)
    {
        case '(': add_token(scanner, LEFT_PAREN, NULL); break;
        case ')': add_token(scanner, RIGHT_PAREN, NULL); break;
        case '{': add_token(scanner, LEFT_BRACE, NULL); break;
        case '}': add_token(scanner, RIGHT_BRACE, NULL); break;
        case ',': add_token(scanner, COMMA, NULL); break;
        case '.': add_token(scanner, COMMA, NULL); break;
        case '-': add_token(scanner, MINUS, NULL); break;
        case '+': add_token(scanner, PLUS, NULL); break;
        case ';': add_token(scanner, SEMICOLON, NULL); break;
        case '*': add_token(scanner, STAR, NULL); break;

        default:
            break;
    }
}

int is_at_end(scanner_t *scanner)
{
    return scanner->current >= scanner->source_length;
}

char advance(scanner_t *scanner)
{
    char c = scanner->source[scanner->current++];
    return c;
}

void add_token(scanner_t *scanner, token_type type,  void *literal)
{
    int lexeme_length = scanner->current - scanner->start;
    char *text = malloc(sizeof(char) * (lexeme_length + 1));
    strncpy(text, scanner->source + scanner->start, lexeme_length);

    token_node_t *a_token = new_token_node(type, text, literal, scanner->line);
    token_list_add(scanner->tokens, a_token);
}