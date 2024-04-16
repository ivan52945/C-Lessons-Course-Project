#pragma once

typedef enum {
    err,
    clc,
    help,
} status;

typedef struct {
    int month;
    char path[60];
    status stat;
} args_res;

args_res read_args(int argc, char* argv []);

void print_help(void);