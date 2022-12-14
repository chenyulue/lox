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

extern int has_error;

void run_file(const char *path);
void run_prompt(void);
void run(char *source);
void error(int line, const char *message);
void report(int line, const char *where, const char *message);
char *read_line(void);
char *read_all_content(const char *path);
size_t get_file_size(FILE *fd);

#endif