#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "scanner.h"
#include "token.h"
#include "lox.h"

#define STR_EQ(X, Y) (strcmp((X), (Y)) == 0)

static token_type keywords_get(char *key);

scanner_t *new_scanner(char *source)
{
    scanner_t *a_scanner = malloc(sizeof(scanner_t));

    a_scanner->source = malloc(strlen(source) + 1);
    strcpy(a_scanner->source, source);

    token_list_t *tokens = new_token_list();
    a_scanner->tokens = tokens;

    a_scanner->start = 0;
    a_scanner->current = 0;
    a_scanner->line = 1;

    a_scanner->source_length = strlen(source);

    return a_scanner;
}

void scanner_del(scanner_t *scanner)
{
    free(scanner->source);
    token_list_del(scanner->tokens);
    free(scanner);
}

token_list_t *scan_tokens(scanner_t *scanner)
{
    while (!is_at_end(scanner))
    {
        scanner->start = scanner->current;
        scan_token(scanner);
    }

    token_node_t *a_new_token_node = new_token_node(END_OF_FILE, "", NULL, scanner->line);
    token_list_add(scanner->tokens, a_new_token_node);

    return scanner->tokens;
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
        case '!':
            add_token(scanner, match(scanner, '=') ? BANG_EQUAL : BANG, NULL);
            break;
        case '=': 
            add_token(scanner, match(scanner, '=') ? EQUAL_EQUAL : EQUAL, NULL);
            break;
        case '<':
            add_token(scanner, match(scanner, '=') ? LESS_EQUAL : LESS, NULL);
            break;
        case '>':
            add_token(scanner, match(scanner, '=') ? GREATER_EQUAL : GREATER, NULL);
            break;
        case '/':
            if (match(scanner, '/')) {
                while (peek(scanner) != '\n' && !is_at_end(scanner)) advance(scanner);
            } else
            {
                add_token(scanner, SLASH, NULL);
            }
            break;
        case ' ':
        case '\r':
        case '\t': break;
        case '\n': scanner->line++; break;
        case '"': string(scanner); break;

        default:
            if (isdigit(c))
            {
                number(scanner);
            } else if (is_alpha(c)) {
                identifier(scanner);
            }
            else {
                error(scanner->line, "Unexpected character.");
            }
            break;
    }
}

void identifier(scanner_t *scanner)
{
    while (is_alpha_numeric(peek(scanner))) advance(scanner);

    char *text = substring(scanner->source, scanner->start, scanner->current);
    token_type type = keywords_get(text);
    add_token(scanner, type, NULL);
    free(text);
}

void number(scanner_t *scanner)
{
    while (isdigit(peek(scanner))) advance(scanner);

    // Look for a fractional part.
    if (peek(scanner) == '.' && isdigit(peek_next(scanner))) {
        // Consume the "."
        advance(scanner);

        while (isdigit(peek(scanner))) advance(scanner);
    }

    double number = atof(scanner->source + scanner->start);
    add_token(scanner, NUMBER, &number);
}

void string(scanner_t *scanner)
{
    while (peek(scanner) != '"' && !is_at_end(scanner))
    {
        if (peek(scanner) == '\n') scanner->line++;
        advance(scanner);
    }

    if (is_at_end(scanner))
    {
        error(scanner->line, "Unterminated string.");
        return;
    }

    // The closing ".
    advance(scanner);

    // Trim the surrounding quotes
    char *value = substring(scanner->source, scanner->start + 1, scanner->current - 1);
    add_token(scanner, STRING, value);
    free(value);
}

int match(scanner_t *scanner, char expected)
{
    if (is_at_end(scanner)) return 0;
    if (scanner->source[scanner->current] != expected) return 0;

    scanner->current++;
    return 1;
}

char peek(scanner_t *scanner)
{
    if (is_at_end(scanner)) return '\0';
    return scanner->source[scanner->current];
}

char peek_next(scanner_t *scanner)
{
    if (scanner->current + 1 >= scanner->source_length) return '\0';
    return scanner->source[scanner->current + 1];
}

int is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

int is_alpha_numeric(char c)
{
    return is_alpha(c) || isdigit(c);
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
    char *text = substring(scanner->source, scanner->start, scanner->current);

    token_node_t *a_token = new_token_node(type, text, literal, scanner->line);
    token_list_add(scanner->tokens, a_token);

    free(text);
}

char *substring(char *source, int start, int end)
{
    int string_length = end - start;
    char *value = malloc(sizeof(char) * (string_length + 1));
    strncpy(value, source + start, string_length);
    value[string_length] = '\0';
    return value;
}

static token_type keywords_get(char *key)
{
    if STR_EQ(key, "false") return FALSE;
    else if STR_EQ(key, "for") return FOR;
    else if STR_EQ(key, "fun") return FUN;
    else if STR_EQ(key, "if") return IF;
    else if STR_EQ(key, "nil") return NIL;
    else if STR_EQ(key, "or") return OR;
    else if STR_EQ(key, "print") return PRINT;
    else if STR_EQ(key, "return") return RETURN;
    else if STR_EQ(key, "super") return SUPER;
    else if STR_EQ(key, "this") return THIS;
    else if STR_EQ(key, "true") return TRUE;
    else if STR_EQ(key, "var") return VAR;
    else if STR_EQ(key, "while") return WHILE;
    else return IDENTIFIER;
}