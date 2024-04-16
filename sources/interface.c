#include "../headers/interface.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

args_res read_args(int argc, char* argv []) {
    args_res out;
    int err_c = 0;
    int hlp_c = 0;
    int mnth_c = 0;
    int clc_c = 0;
    int result = 0;

    while((result = getopt(argc, argv, "hf:m:")) != -1) {
        switch(result) {
            case 'h':
                puts("help\n");
                hlp_c = 1;
                break;
            case 'f':
                clc_c = 1;
                strcpy(out.path, optarg);
                break;
            case 'm':
                mnth_c = 1;
                out.month = atoi(optarg);
                break;
            case '?':
                puts("useless\n");
                err_c = 1;
                break;
        }
    }
    // checking correct args
    if(err_c) {
        out.stat = err;
        return out;
    }
    else if(hlp_c && (mnth_c || clc_c)) {
        out.stat = err;
        printf("Error: arg help must be without other args\n");
        return out;
    }
    else if(mnth_c && !clc_c) {
        out.stat = err;
        printf("Error: arg file is missed\n");
        return out;
    }
    // input status to output structure
    if(!hlp_c) {
        out.stat = clc;
        out.month = mnth_c;
    }

    else
        out.stat = help;
    return out;
}

void print_help(void) {
    printf(" -h                              HELP\n");
    printf(" -f [path to file]               OUTPUT STATISTICS\n");
    printf(" -f [path to file] -m [mounth]   OUTPUT STATISTICS CURRENT MOUNTH\n");
}