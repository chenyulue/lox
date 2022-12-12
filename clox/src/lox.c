#include <stdio.h>
#include <stdlib.h>

#include "lox.h"
#include "token.h"
#include "scanner.h"

int main(int argc, char** argv)
{
    int has_error = 0;

    if (argc > 2)
    {
        fprintf(stderr, "Usage: clox [script]\n");
        exit(1);
    } else if (argc == 2)
    {
        run_file(argv[1], &has_error);
    } else
    {
        run_prompt(&has_error);
    }

    return EXIT_SUCCESS;
}

static void run_file(const char *path, int *has_error)
{
    char *source = read_all_content(path);
    run(source, has_error);
    free(source);

    if (*has_error) exit(1);
}

static void run_prompt(int *has_error)
{
    while (1) {
        printf("> ");
        char *line = read_line();
        if (line == NULL) break;
        run(line);
        free(line);

        *has_error = 0;
    }
}

static void run(char *source)
{
    scanner_t *scanner = new_scanner(source);
    token_list_t *tokens = scan_tokens(scanner);

    // For now, just print the tokens
    token_t *token = tokens->head;
    while (token != NULL)
    {
        print_token(token);
    }
    scanner_del(scanner);
    token_list_del(tokens);
}

static void error(int line, const char *message, int *has_error)
{
    report(line, "", message, has_error);
}

static void report(int line, const char *where, const char *message, int *has_error)
{
    fprintf(stderr, "[line %d] Error %s: %s\n", line, where, message);
    *has_error = 1;
}

static char *read_line(void)
{
    int max_size = 1024;
    int size = 0;
    char *input = NULL;
    
    while (1)
    {
        int c = fgetc(stdin);
        if (c == EOF) return NULL;
        if (size + 2 > max_size || input == NULL) {
            max_size *= 2;
            char *re_input = realloc(input, max_size * sizeof(char));
            if (re_input == NULL)
            {
                fprintf(stderr, "Allocation failed when reading.\n");
                if (input) free(input);
                exit(1);
            }
            input = re_input;
        }
        input[size++] = c;

        if (c == '\n') break;
    }
    input[size] = '\0';

    return input;
}

static char *read_all_content(const char *path)
{
    FILE *fd = fopen(path, "r");
    ASSERT_SUCCESS(fd, "Can't open the source file: %s\n", path);

    size_t size = get_file_size(fd);
    char *source = malloc(size + 1);
    fread(source, sizeof(char), size, fd);
    int read_error = ferror(fd);
    fclose(fd);
    
    ASSERT_SUCCESS(!read_error, "Error in reading source file: %s\n", path);

    return source;
}

static size_t get_file_size(FILE *fd)
{
    fseek(fd, 0, SEEK_END);
    size_t size = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    return size;
}
