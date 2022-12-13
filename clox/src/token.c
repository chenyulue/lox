#include <stdlib.h>
#include <stdio.h>
#include "token.h"

token_t *new_token(token_type type, const char *lexeme, void *literal, int line)
{
    token_t *a_token = malloc(sizeof(token_t));

    if (a_token == NULL)
    {
        fprintf(stderr, "Allocation for tokens failed.\n");
        return NULL;
    }

    a_token->type = type;

    a_token->lexeme = malloc(strlen(lexeme) + 1);
    strcpy(a_token->lexeme, lexeme);

    switch (type)
    {
        case NUMBER:
            a_token->literal = malloc(sizeof(double));
            memcpy(a_token->literal, literal, sizeof(double));
            break;
        case STRING:
            a_token->literal = malloc(strlen((char*)literal) + 1);
            strcpy(a_token->literal, (const char*)literal);
            break;
        default:
            a_token->literal = literal;
            break;
    }

    a_token->line = line;

    return a_token;
}

void token_del(token_t *token)
{
    free(token->lexeme);
    free(token->literal);
    free(token);
}

void print_token(token_t *token)
{
    switch (token->type)
    {
    case NUMBER:
        printf("%s %s %g", token_name(token->type), token->lexeme, *(double*)token->literal);
        break;
    case STRING:
        printf("%s %s %s", token_name(token->type), token->lexeme, (char*)token->literal);
        break;
    default:
        printf("%s %s null", token_name(token->type), token->lexeme);
        break;
    }
}

token_list_t *new_token_list(void)
{
    token_list_t *a_token_list = malloc(sizeof(token_list_t));
    a_token_list->head = NULL;
    a_token_list->tail = NULL;
    a_token_list->size = 0;
    return a_token_list;
}

void token_list_add(token_list_t *tokens, token_node_t *token)
{
    if (tokens->head == NULL)
    {
        tokens->head = token;
        tokens->tail = token;
    } else
    {
        tokens->tail->next = token;
        tokens->tail = token;
    }
    tokens->size++;
}

void token_list_del(token_list_t *tokens)
{
    token_node_t *current = tokens->head;
    while (current)
    {
        token_node_t *next = current->next;
        token_node_del(current);
        current = next;
    }
    free(tokens);
}

token_node_t *new_token_node(token_type type, char *lexeme, void *literal, int line)
{
    token_node_t *a_new_token_node = malloc(sizeof(token_node_t));
    a_new_token_node->token = new_token(type, lexeme, literal, line);
    a_new_token_node->next = NULL;
    return a_new_token_node; 
}

void token_node_del(token_node_t *token_node)
{
    token_del(token_node->token);
    free(token_node);
}

char *token_name(token_type type)
{
    switch (type)
    {
        case LEFT_PAREN: return "LEFT_PAREN";
        case RIGHT_PAREN: return "RIGHT_PAREN";
        case LEFT_BRACE: return "LEFT_BRACE";
        case RIGHT_BRACE: return "RIGHT_BRACE";
        case COMMA: return "COMMA";
        case DOT: return "DOT";
        case MINUS: return "MINUS";
        case PLUS: return "PLUS";
        case SEMICOLON: return "SEMICOLON";
        case SLASH: return "SLASH";
        case STAR: return "STAR";
        case BANG: return "BANG";
        case BANG_EQUAL: return "BANG_EQUAL";
        case EQUAL: return "EQUAL";
        case EQUAL_EQUAL: return "EQUAL_EQUAL";
        case GREATER: return "GREATER";
        case GREATER_EQUAL: return "GREATER_EQUAL";
        case LESS: return "LESS";
        case LESS_EQUAL: return "LESS_EQUAL";
        case IDENTIFIER: return "IDENTIFIER";
        case STRING: return "STRING";
        case NUMBER: return "NUMBER";
        case AND: return "AND";
        case CLASS: return "CLASS";
        case ELSE: return "ELSE";
        case FALSE: return "FALSE";
        case FUN: return "FUN";
        case FOR: return "FOR";
        case IF: return "IF";
        case NIL: return "NIL";
        case OR: return "OR";
        case PRINT: return "PRINT";
        case RETURN: return "RETURN";
        case SUPER: return "SUPER";
        case THIS: return "THIS";
        case TRUE: return "TRUE";
        case VAR: return "VAR";
        case WHILE: return "WHILE";
        default: return "END_OF_FILE";
    }
}