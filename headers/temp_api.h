#pragma once
#include "t_record_type.h"

char t_average_mount(unsigned long n_rec, t_record_t a [], int month, t_record_vect_t month_vect []);

char t_min_month(unsigned long n_rec, t_record_t a [], int month, t_record_vect_t month_vect []);

char t_max_month(unsigned long n_rec, t_record_t a [], int month, t_record_vect_t month_vect []);

char t_average_year(unsigned long n_rec, t_record_t a []);

char t_min_year(unsigned long n_rec, t_record_t a []);

char t_max_year(unsigned long n_rec, t_record_t a []);

void print_month_statistics(unsigned long n_rec, t_record_t a [], int month, t_record_vect_t month_vect []);

void print_year_statistics(unsigned long n_rec, t_record_t a [], t_record_vect_t month_vect []);