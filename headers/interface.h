#pragma once

typedef enum {
    err,
    clc_m,
    clc,
    help,
} status;

typedef struct {
    int month;
    char path[60];
    status stat;
} args_res;

void read_args(int argc, char* argv [], args_res* out);

void print_help(void);