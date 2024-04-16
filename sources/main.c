#include <stdio.h>
#include <stdlib.h>

#include "../headers/temp_api.h"
#include "../headers/interface.h"
#include "../headers/files_api.h"

int main(int argc, char* argv []) {
    args_res in = read_args(argc, argv);

    if(in.stat == clc) {
        t_record* month_p_arr[12] = { 0 };

        printf("read stats from file %s\n", in.path);

        unsigned long max_size = n_records_in_csv(in.path);

        t_record* a = malloc(sizeof(t_record) * max_size);

        unsigned long n_rec = read_file_csv(in.path, a, month_p_arr);

        if(in.month) {
            int t_average = t_average_mount(n_rec, a, in.month, month_p_arr);
            int t_min = t_min_month(n_rec, a, in.month, month_p_arr);
            int t_max = t_max_month(n_rec, a, in.month, month_p_arr);

            printf("average temperature in month %d is %d degrees C\n", in.month, t_average);
            printf("minimal temperature in month %d is %d degrees C\n", in.month, t_min);
            printf("maximal temperature in month %d is %d degrees C\n", in.month, t_max);
        }
        else {
            int t_average = t_average_year(n_rec, a);
            int t_min = t_min_year(n_rec, a);
            int t_max = t_max_year(n_rec, a);

            printf("average temperature in year is %d degrees C\n", t_average);
            printf("minimal temperature in year is %d degrees C\n", t_min);
            printf("maximal temperature in year is %d degrees C\n", t_max);
        }

        free(a);
    }
    else
        print_help();

    return 0;
}