#include <math.h>
#include <stdio.h>

#include "../headers/temp_api.h"

char t_average(unsigned long n_rec, t_record a []) {
    long long sum = 0;
    char average;

    for(int i = 0; i < n_rec; i++)
        sum += a[i].temp;

    average = (n_rec > 0) ? round(sum * 1.0 / n_rec) : -120;

    return average;
}

char t_min(unsigned long n_rec, t_record a []) {
    char min = 120;

    for(int i = 0; i < n_rec; i++) {
        min = (min > a[i].temp) ? a[i].temp : min;
    }

    return min;
}

char t_max(unsigned long n_rec, t_record a []) {
    char max = -120;

    for(int i = 0; i < n_rec; i++)
        max = (max < a[i].temp) ? a[i].temp : max;

    return max;
}



char t_average_mount(unsigned long n_rec, t_record a [], int month, t_record_vect month_vect []) {
    t_record_vect mnt_s = month_vect[month - 1];

    if(mnt_s.n)
        return  t_average(mnt_s.n, mnt_s.vect);
    else
        return -120;
}

char t_min_month(unsigned long n_rec, t_record a [], int month, t_record_vect month_vect []) {
    t_record_vect mnt_s = month_vect[month - 1];

    if(mnt_s.n)
        return t_min(mnt_s.n, mnt_s.vect);
    else
        return -120;
}

char t_max_month(unsigned long n_rec, t_record a [], int month, t_record_vect month_vect []) {
    t_record_vect mnt_s = month_vect[month - 1];

    if(mnt_s.n)
        return t_max(mnt_s.n, mnt_s.vect);
    else
        return -120;
}

char t_average_year(unsigned long n_rec, t_record a []) {
    return t_average(n_rec, a);
}

char t_min_year(unsigned long n_rec, t_record a []) {
    return t_min(n_rec, a);
}

char t_max_year(unsigned long n_rec, t_record a []) {
    return t_max(n_rec, a);
}

void print_month_statistics(unsigned long n_rec, t_record a [], int month, t_record_vect month_vect []) {
    if(month_vect[month].vect) {
        int t_average = t_average_mount(n_rec, a, month, month_vect);
        int t_min = t_min_month(n_rec, a, month, month_vect);
        int t_max = t_max_month(n_rec, a, month, month_vect);

        printf("Month  Average  Minimal  Maximal\n");
        printf("%3d      %3d      %3d      %3d\n", month, t_average, t_min, t_max);
    }
    else
        printf("There are no data for month %d", month);
}

void print_year_statistics(unsigned long n_rec, t_record a [], t_record_vect month_vect []) {
    printf("Month  Average  Minimal  Maximal\n");
    for(int i = 0; i < 12; i++)
        if(month_vect[i].vect) {
            int t_average = t_average_mount(n_rec, a, i, month_vect);
            int t_min = t_min_month(n_rec, a, i, month_vect);
            int t_max = t_max_month(n_rec, a, i, month_vect);
            printf("%3d\t%3d\t %3d\t  %3d\n", i, t_average, t_min, t_max);
        }

    int t_average = t_average_year(n_rec, a);
    int t_min = t_min_year(n_rec, a);
    int t_max = t_max_year(n_rec, a);

    printf("average temperature in year is %d degrees C\n", t_average);
    printf("minimal temperature in year is %d degrees C\n", t_min);
    printf("maximal temperature in year is %d degrees C\n", t_max);
}