
#ifndef MAIN_H
#define MAIN_H
#include <getopt.h>
#include <stdio.h>
#include <unistd.h>

static short VERBOSITY = 0;
static const short VERBOSITY_MIN = 0;
static const short VERBOSITY_MAX = 4;

/* Print a help text for app usage */
void usage()
{
    printf("Usage: calculator [option]\n");
    printf("-h - print this help text\n");
    printf("-v - run in verbose mode\n");
}

/* TODO: probably move to 'common.h' for use by other apps? */
/* Print a logging message. 'level' = -1 means it's an error message. */
void log_message(const char* message, const short level)
{
    if (level == -1) fprintf(stderr, "%s\n", message);
    else if (level >= VERBOSITY) fprintf(stdout, "%s\n", message);
}

/* 
    Use 'getopt' to process command-line arguments 
    Return codes:
    -1 - failed processing, exit program with error in 'main'
    0 - successful return and continue program
    1 - help message triggered, exit program as successful in 'main'
*/
int process_cmdline_args(const int argc, char *const *argv)
{
    char choice, *input_endptr;
    long input_value;

    while ( (choice = getopt(argc, argv, "v:h")) != -1 )
    {
        switch(choice) {
            case 'v':
                input_value = strtol(optarg, &input_endptr, 10);

                /* No numeric input value found */
                if (input_endptr == optarg) {
                    log_message("Verbosity level has to be an integer!", -1);
                    return -1;
                } else if ( (input_value > VERBOSITY_MAX) || (input_value < VERBOSITY_MIN) )
                {
                    log_message("Verbosity level value out of range! [0-4]", -1);
                    return -1;
                }
                VERBOSITY = (short) input_value;
                break;
            case 'h':
                usage();
                return 0;
            default:
                usage();
                return -1;
        }
    }
    return 0;
}

#endif /* !MAIN_H */
