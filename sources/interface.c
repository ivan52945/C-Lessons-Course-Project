#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../headers/interface.h"

/**
 * @brief Parses command-line arguments and returns processing results.
 *
 * This function uses getopt() to parse command-line options in format: \n
 *   - -h       : show help                                             \n
 *   - -f <path>: specify file path (required for calculations)         \n
 *   - -m <num> : specify month (1-12, requires -f)                     \n
 *
 * @param argc Argument count (from main())
 * @param argv Argument values (from main())
 * @return args_res_t Structure containing:                             \n
 *         - month: parsed month (0 if not specified)                   \n
 *         - path:  file path (if -f specified)                         \n
 *         - stat:  processing status (err/clc/help)                    \n
 *
 * @note Validation rules:
 *       - -h cannot be combined with other options                     \n
 *       - -m requires -f                                               \n
 *       - month must be 1-12                                           \n
 *       - -f is mandatory for calculations                             \n
 */
args_res_t read_args(int argc, char* argv [])
{
    int err_c = 0;
    int month_c = 0;
    args_res_t out = {0};
    int help_c = 0;
    int clc_c = 0;
    int result = 0;

    while((result = getopt(argc, argv, "hf:m:")) != -1) {
        switch(result) {
            case 'h':
                help_c = 1;
                break;
            case 'f':
                clc_c = 1;
                strcpy(out.path, optarg);
                break;
            case 'm':
                month_c = 1;
                out.month = atoi(optarg);
                break;
            case '?':
            default:
                err_c = 1;
                break;
        }
    }

    if(err_c) {
        out.stat = err;
        return out;
    }
    else if(help_c && (month_c || clc_c)) {
        out.stat = err;
        fprintf(stderr, "Error: arg help must be without other args\n");
        return out;
    }
    else if(month_c && !clc_c) {
        out.stat = err;
        fprintf(stderr, "Error: arg file is missed\n");
        return out;
    }
    else if(month_c && (out.month < 1 || out.month > 12)) {
        out.stat = err;
        fprintf(stderr,"Error: arg month must be num between 1 and 12\n");
        return out;
    }

    out.month = (month_c) ? out.month : 0;

    out.stat = (clc_c) ? clc : help;

    return out;
}
/**
 * @brief Displays command line usage instructions
 *
 * Prints formatted help message showing all available program options
 */
void print_help(void)
{
    printf(" -h                              HELP\n");
    printf(" -f [path to file]               OUTPUT STATISTICS\n");
    printf(" -f [path to file] -m [mounth]   OUTPUT STATISTICS CURRENT MOUNTH\n");
}