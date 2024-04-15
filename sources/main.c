#include <stdio.h>
#include "../headers/temp_api.h"
#include "../headers/interface.h"

int main(int argc, char* argv []) {
    args_res in;
    read_args(argc, argv, &in);

    if(in.stat == clc)
        printf("year stats from file %s", in.path);
    else if(in.stat == clc_m)
        printf("stats from file %s in month %d", in.path, in.month);
    else
        print_help();

    return 0;
}