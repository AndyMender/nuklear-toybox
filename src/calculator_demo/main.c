
#include <stdio.h>
#include <stdlib.h>

#define NK_IMPLEMENTATION
#include <nuklear.h>

#include "main.h"

void usage();
int process_cmdline_args(const int, char *const *);
void log_message(const char*, const short);

int main(const int argc, char *const *argv)
{
    int exit_code = 0;

    exit_code = process_cmdline_args(argc, argv);

    /* Triggered 'help' message */
    if (exit_code == 1) return EXIT_SUCCESS;
    else if (exit_code == -1) {
        log_message("Processing command-line arguments failed. Exiting!", -1);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}