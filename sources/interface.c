#include "../headers/interface.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

args_res read_args(int argc, char* argv []) {

    args_res out;
    int err_c = 0;
    int month_c = 0;
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
                err_c = 1;
                break;
        }
    }
    // checking correct args
    if(err_c) {
        out.stat = err;
        return out;
    }
    else if(help_c && (month_c || clc_c)) {
        out.stat = err;
        printf("Error: arg help must be without other args\n");
        return out;
    }
    else if(month_c && !clc_c) {
        out.stat = err;
        printf("Error: arg file is missed\n");
        return out;
    }
    else if(month_c && (out.month < 1 || out.month > 12)) {
        out.stat = err;
        printf("Error: arg mounth must be num between 1 and 12\n");
        return out;
    }

    out.month = (month_c) ? out.month : 0;

    out.stat = (clc_c) ? clc : help;

    return out;
}

void print_help(void) {
    printf(" -h                              HELP\n");
    printf(" -f [path to file]               OUTPUT STATISTICS\n");
    printf(" -f [path to file] -m [mounth]   OUTPUT STATISTICS CURRENT MOUNTH\n");
}