#pragma once
#include "t_record_type.h"

char t_average_mount(int month, t_record_vect_t month_vect []);

char t_min_month(int month, t_record_vect_t month_vect []);

char t_max_month(int month, t_record_vect_t month_vect []);

char t_average_year(t_record_vect_t year_vect);

char t_min_year(t_record_vect_t year_vect);

char t_max_year(t_record_vect_t year_vect);

void print_month_statistics(int month, t_record_vect_t month_vect []);

void print_year_statistics(t_record_vect_t year_vect, t_record_vect_t month_vect[]);