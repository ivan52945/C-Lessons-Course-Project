#include <stdio.h>
#include <stdlib.h>

#include "../headers/temp_api.h"
#include "../headers/interface.h"
#include "../headers/files_api.h"

int main(int argc, char* argv []) {
    args_res in = read_args(argc, argv);

    if(in.stat == clc) {
        t_record* month_p_arr[12] = { 0 };

        t_record_vect a = read_file_csv(in.path, month_p_arr);

        if(in.month) {
            if(month_p_arr[in.month]) {
                int t_average = t_average_mount(a.n, a.vect, in.month, month_p_arr);
                int t_min = t_min_month(a.n, a.vect, in.month, month_p_arr);
                int t_max = t_max_month(a.n, a.vect, in.month, month_p_arr);

                printf("average temperature in month %d is %d degrees C\n", in.month, t_average);
                printf("minimal temperature in month %d is %d degrees C\n", in.month, t_min);
                printf("maximal temperature in month %d is %d degrees C\n", in.month, t_max);
            }
            else
                printf("There are no data for month %d", in.month);
        }
        else {
            int t_average = t_average_year(a.n, a.vect);
            int t_min = t_min_year(a.n, a.vect);
            int t_max = t_max_year(a.n, a.vect);

            printf("average temperature in year is %d degrees C\n", t_average);
            printf("minimal temperature in year is %d degrees C\n", t_min);
            printf("maximal temperature in year is %d degrees C\n", t_max);
        }

        free(a.vect);
    }
    else
        print_help();

    return 0;
}