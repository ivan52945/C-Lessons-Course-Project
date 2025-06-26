#pragma once

/**
 * @enum  status
 * @brief Command line arguments parsing status
 *
 * Describes whether the provided command-line arguments are valid
 * and what action the program should take.
 */
typedef enum {
    err,            ///< Error
    clc,            ///< Calculate
    help,           ///< Help
} status;

/**
 * @struct args_res_t
 * @brief Command line arguments processing result
 *
 * Stores validated input data and parsing status.
 */
typedef struct {
    int month;      ///< Target month number (1-12)
    char path[60];  ///< Path of file with temperature records
    status stat;    ///< Parsing status (see @ref status)
} args_res_t;

args_res_t read_args(int argc, char* argv []);

void print_help(void);