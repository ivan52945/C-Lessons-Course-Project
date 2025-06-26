#pragma once
#include "t_record_type.h"
#include "stdio.h"

FILE* open_file(char name[], char format[]);

unsigned long n_records_in_csv(char in[]);

unsigned long read_file_csv(char in[], t_record_t a[], t_record_vect_t month_p[]);

t_record_vect_t get_vect_from_file_csv(char in[], t_record_vect_t month_p[]);