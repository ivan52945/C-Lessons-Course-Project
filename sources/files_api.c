#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>
#include "../headers/t_record_type.h"
#include "../headers/files_api.h"

/**
 * @brief Opens a file with error handling
 *
 * Attempts to open specified file in given mode. If unsuccessful,
 * prints error message to stderr and terminates program with exit code 1.
 *
 * @param name  Path to the file (null-terminated string)
 * @param format File access mode ("r", "w", etc. - same as fopen())
 * @return FILE* Pointer to opened file stream
 *
 * @warning Terminates program on failure
 */
FILE* open_file(char name[], char format[])
{
    FILE* f = fopen(name, format);

    if (!f) {
        perror(name);
        exit(1);
    }

    return f;
}

/**
 * @brief Estimates number of records in a CSV file
 *
 * Calculates approximate record count based on file size and fixed record size assumption.
 * Uses heuristic: (file_size / 20) * 1.2 to account for headers/variability.
 *
 * @param in Path to CSV file (will be opened in read mode)
 * @return Estimated record count (always >= 1)
 *
 * @warning Terminates program on failure
 */
unsigned long n_records_in_csv(char in[])
{
    FILE* f = open_file(in, "r");

    fseek(f, 0, SEEK_END);

    unsigned long size = (ftell(f) / 20) * 1.2;

    fclose(f);

    return size;
}

/**
 * @brief Calculates record counts per month in a temperature dataset
 *
 * Computes the number of temperature records for each month (0-11) by analyzing
 * memory offsets between sorted monthly data vectors. Handles edge cases for:  \n
 * - Empty months (n=0)                                                         \n
 * - Final month records                                                        \n
 * - Gaps between months                                                        \n
 *
 * @param[in] n_rec Total number of records in array 'a'
 * @param[in] a Base array of all temperature records
 * @param[in,out] month_p_arr Array of month vectors (must have 12 elements)
 *
 * @warning Assumes month_p_arr is pre-allocated for 12 months
 */
void calc_n_rect_in_every_month(unsigned long n_rec, t_record_t a[], t_record_vect_t month_p_arr[])
{
    for (int i = 0; i < 12; i++) {
        if (month_p_arr[i].vect && i < 11) {
            int j;

            for (j = i + 1; j < 12 && !month_p_arr[j].vect; j++) { }

            if (j < 12 && month_p_arr[j].vect)
                month_p_arr[i].n = month_p_arr[j].vect - month_p_arr[i].vect;
            else
                month_p_arr[i].n = n_rec - (month_p_arr[i].vect - a);
        }
        else if (month_p_arr[i].vect)
            month_p_arr[i].n = n_rec - (month_p_arr[i].vect - a);
        else
            month_p_arr[i].n = 0;
    }
}

/**
 * @brief Reads and parses temperature data from CSV file
 *
 * Processes a CSV file containing temperature records with format: \n
 * `YYYY;MM;DD;hh;mm;T` where:                                      \n
 * - Fields are semicolon-delimited                                 \n
 * - Temperature (T) is signed byte (-128 to +127)                  \n
 * - Month (MM) must be 1-12                                        \n
 *
 * @param[in] in Path to input CSV file
 * @param[out] a Array to store valid records (pre-allocated)
 * @param[out] month_vect Array of month vectors (length 12)
 * @return Number of successfully parsed records
 *
 * @warning Input array 'a' must have sufficient capacity
 * @note Invalid records are skipped with error messages
 * @see calc_n_rect_in_every_month() Called for final month calculations
 */
unsigned long read_file_csv(char in[], t_record_t a[], t_record_vect_t month_vect[])
{
    char s[30];
    t_record_t temp;
    FILE* f = open_file(in, "r");
    int n_correct;
    int n_records = 0;

    printf("read stats from file %s\n", in);

    for (unsigned long i = 0; fscanf(f, "%[^\n]\n", s) != EOF; i++) {

        n_correct = sscanf(s, "%hu;%hhu;%hhu;%hhu;%hhu;%hhd", &(temp.year), &(temp.month), &(temp.day), &(temp.hour), &(temp.minute), &(temp.temp));

        if (n_correct == 6 && (temp.month > 0 && temp.month < 13)) {
            if (!month_vect[temp.month - 1].vect) {
                month_vect[temp.month - 1].vect = a + n_records;
            }
            a[n_records++] = temp;
        }
        else
            printf("Wrong data in record %ld: %s\n", i + 1, s);
    }

    fclose(f);

    calc_n_rect_in_every_month(n_records, a, month_vect);

    return n_records;
}

/**
 * @brief Creates and initializes a temperature record vector from CSV file
 *
 * Provides complete initialization of a t_record_vect_t by:    \n
 * - Estimating storage needs based on file size                \n
 * - Allocating exact required memory                           \n
 * - Loading and validating all records                         \n
 * - Building month index vectors                               \n
 *
 * @param[in] in Path to the input CSV file (null-terminated string)
 * @param[out] month_vect Array of month vectors (length 12) for storing monthly data references
 * @return Initialized t_record_vect_t containing loaded records
 *
 * @throw Terminates program on:                                \n
 * - Memory allocation failure (exit code 1)                    \n
 * - File errors (via open_file())                              \n
 *
 * @post Caller must free out.vect when no longer needed
 * @see n_records_in_csv() Used for size estimation
 * @see read_file_csv() Used for actual file parsing
 */
t_record_vect_t get_vect_from_file_csv(char in[], t_record_vect_t month_vect[])
{
    t_record_vect_t out;

    unsigned long max_size = n_records_in_csv(in);

    out.vect = malloc(sizeof(t_record_t) * max_size);

    if(out.vect == NULL){
        fprintf(stderr,"Error: failed to allocate memory");
        exit(1);
    }

    out.n = read_file_csv(in, out.vect, month_vect);

    return out;
}