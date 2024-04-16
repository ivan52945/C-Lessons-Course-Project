#pragma once
#include "t_record_type.h"

char t_average_mount(unsigned long n_rec, t_record a [], int month_i, t_record* months []);

char t_min_mounth(unsigned long n_rec, t_record a [], int month_i, t_record* months []);

char t_max_mounth(unsigned long n_rec, t_record a [], int month_i, t_record* months []);

char t_average_year(unsigned long n_rec, t_record a []);

char t_min_year(unsigned long n_rec, t_record a []);

char t_max_year(unsigned long n_rec, t_record a []);