#include <stdio.h>
#include <stdlib.h>

#include "../headers/temp_api.h"
#include "../headers/interface.h"
#include "../headers/files_api.h"

int main(int argc, char* argv []) {
    args_res in = read_args(argc, argv);

    if(in.stat == clc) {
        t_record* month_p_arr[12] = { 0 };

        t_record_vect a = get_vect_from_file_csv(in.path, month_p_arr);

        if(in.month)
            print_month_statistics(a.n, a.vect, in.month, month_p_arr);
        else
            print_year_statistics(a.n, a.vect);

        free(a.vect);
    }
    else
        print_help();

    return 0;
}