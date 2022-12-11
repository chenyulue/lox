#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        fprintf(stderr, "Usage: clox [script]\n");
        exit(1);
    } else if (argc == 2)
    {
        run_file(argv[1]);
    } else
    {
        run_prompt();
    }

    return EXIT_SUCCESS;
}
