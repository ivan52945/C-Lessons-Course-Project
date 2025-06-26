#include <stdlib.h>

#include "../headers/temp_api.h"
#include "../headers/interface.h"
#include "../headers/files_api.h"

int main(int argc, char* argv [])
{
    args_res_t in = read_args(argc, argv);

    if(in.stat == clc) {
        t_record_vect_t  month_vect[12] = {};

        t_record_vect_t  a = get_vect_from_file_csv(in.path, month_vect);

        if(in.month)
            print_month_statistics(a.n, a.vect, in.month, month_vect);
        else
            print_year_statistics(a.n, a.vect, month_vect);

        free(a.vect);
    }
    else
        print_help();

    return EXIT_SUCCESS;
}