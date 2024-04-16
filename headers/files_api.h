#pragma once
#include "t_record_type.h"
#include <stdio.h>

FILE* open_file(char name [], char format []);

int n_records_in_csv(char in []);

int read_file_csv(char in [], t_record a [], t_record* month_start []);