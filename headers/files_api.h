#pragma once
#include "t_record_type.h"

FILE* open_file(char name [], char format []);

int n_records_in_csv(char in []);

t_record_vect read_file_csv(char in [], t_record* month_p []);