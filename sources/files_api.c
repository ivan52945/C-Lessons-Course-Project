#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/t_record_type.h"
#include "../headers/files_api.h"

FILE* open_file(char name [], char format []) {
    FILE* f = fopen(name, format);

    if(!f) {
        printf("Error: cannot open file %s for %s", name, format);
        abort();
    }

    return f;
}

int n_records_in_csv(char in []) {
    FILE* f = open_file(in, "r");

    fseek(f, 0, SEEK_END);

    unsigned long size = (ftell(f) / 20) * 1.2;

    fclose(f);

    return size;
}

void calc_n_rect_in_every_month(unsigned long n_rec, t_record a [], t_record_vect month_p_arr []) {
    for(int i = 0; i < 12; i++) {
        if(month_p_arr[i].vect && i < 11) {
            int j;

            for(j = i + 1; j < 12 && !month_p_arr[j].vect; j++) { }

            if(j < 12 && month_p_arr[j].vect)
                month_p_arr[i].n = month_p_arr[j].vect - month_p_arr[i].vect;
            else
                month_p_arr[i].n = n_rec - (month_p_arr[i].vect - a);
        }
        else if(month_p_arr[i].vect)
            month_p_arr[i].n = n_rec - (month_p_arr[i].vect - a);
        else
            month_p_arr[i].n = 0;
    }
}

unsigned long read_file_csv(char in [], t_record a [], t_record_vect month_vect []) {

    char s[30];
    t_record temp;
    FILE* f = open_file(in, "r");
    int n_correct;
    int n_records = 0;

    printf("read stats from file %s\n", in);

    for(int i = 0; fscanf(f, "%[^\n]\n", s) != EOF; i++) {

        n_correct = sscanf(s, "%hu;%hhu;%hhu;%hhu;%hhu;%hhd", &(temp.year), &(temp.month), &(temp.day), &(temp.hour), &(temp.minute), &(temp.temp));

        if(n_correct == 6 && (temp.month > 0 && temp.month < 13)) {
            if(!month_vect[temp.month - 1].vect) {
                month_vect[temp.month - 1].vect = a + n_records;
            }
            a[n_records++] = temp;
        }
        else
            printf("Wrong data in record %d: %s\n", i + 1, s);
    }

    fclose(f);

    calc_n_rect_in_every_month(n_records, a, month_vect);

    return n_records;
}

t_record_vect get_vect_from_file_csv(char in [], t_record_vect month_vect []) {
    t_record_vect out;

    unsigned long max_size = n_records_in_csv(in);

    out.vect = malloc(sizeof(t_record) * max_size);

    out.n = read_file_csv(in, out.vect, month_vect);

    return out;
}