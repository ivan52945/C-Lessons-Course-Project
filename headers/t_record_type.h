#pragma once

typedef struct {
    unsigned short year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    char temp;
} t_record;

typedef struct {
    t_record* vect;
    unsigned long n;
} t_record_vect;