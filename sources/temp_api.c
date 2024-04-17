#include <math.h>
#include <stdio.h>

#include "../headers/temp_api.h"

char t_average(unsigned long n_rec, t_record a []) {
    long long sum = 0;
    char average;

    for(int i = 0; i < n_rec; i++) {
        sum += a[i].temp;
    }

    average = round(sum * 1.0 / n_rec);

    return average;
}

char t_min(unsigned long n_rec, t_record a []) {
    char min = a[0].temp;

    for(int i = 1; i < n_rec; i++) {
        min = (min > a[i].temp) ? a[i].temp : min;
    }

    return min;
}

char t_max(unsigned long n_rec, t_record a []) {
    char max = a[0].temp;

    for(int i = 1; i < n_rec; i++) {
        max = (max < a[i].temp) ? a[i].temp : max;
    }

    return max;
}

unsigned long n_needed_rect(unsigned long n_rec, t_record a [], int month, t_record* month_p_arr []) {
    if(month_p_arr[month - 1]) {
        int i;

        for(i = month; i < 12 && !month_p_arr[i]; i++) { }

        if(i < 11 || (i == 11 && month_p_arr[i]))
            return month_p_arr[month] - month_p_arr[month - 1];
        else
            return n_rec - (month_p_arr[month - 1] - a);
    }
    else
        return 0;
}

char t_average_mount(unsigned long n_rec, t_record a [], int month, t_record* month_p_arr []) {
    t_record* start = month_p_arr[month - 1];

    if(start) {
        int n_needed_rec_out = n_needed_rect(n_rec, a, month, month_p_arr);

        return  t_average(n_needed_rec_out, start);
    }
    else
        return -120;
}

char t_min_month(unsigned long n_rec, t_record a [], int month, t_record* month_p_arr []) {
    t_record* start = month_p_arr[month - 1];

    if(start) {
        int n_needed_rec_out = n_needed_rect(n_rec, a, month, month_p_arr);

        return t_min(n_needed_rec_out, start);
    }
    else
        return -120;
}

char t_max_month(unsigned long n_rec, t_record a [], int month, t_record* month_p_arr []) {
    t_record* start = month_p_arr[month - 1];

    if(start) {
        int n_needed_rec_out = n_needed_rect(n_rec, a, month, month_p_arr);

        return t_max(n_needed_rec_out, start);
    }
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

