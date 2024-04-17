#pragma once
#include "t_record_type.h"

char t_average_mount(unsigned long n_rec, t_record a [], int month, t_record* month_p_arr []);

char t_min_month(unsigned long n_rec, t_record a [], int month, t_record* month_p_arr []);

char t_max_month(unsigned long n_rec, t_record a [], int month, t_record* month_p_arr []);

char t_average_year(unsigned long n_rec, t_record a []);

char t_min_year(unsigned long n_rec, t_record a []);

char t_max_year(unsigned long n_rec, t_record a []);

void print_month_statistics(unsigned long n_rec, t_record a [], int month, t_record* month_p_arr []);

void print_year_statistics(unsigned long n_rec, t_record a []);