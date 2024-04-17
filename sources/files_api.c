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

unsigned long read_file_csv(char in [], t_record a [], t_record* month_p []) {

    char s[30];
    t_record temp;
    FILE* f = open_file(in, "r");
    int n_correct;
    int n_records = 0;

    printf("read stats from file %s\n", in);

    for(int i = 0; fscanf(f, "%[^\n]\n", s) != EOF; i++) {

        n_correct = sscanf(s, "%hu;%hhu;%hhu;%hhu;%hhu;%hhd", &(temp.year), &(temp.month), &(temp.day), &(temp.hour), &(temp.minute), &(temp.temp));

        if(n_correct == 6 && (temp.month > 0 && temp.month < 13)) {
            if(!month_p[temp.month - 1]) {
                month_p[temp.month - 1] = a + n_records;
            }
            a[n_records++] = temp;
        }
        else
            printf("Wrong data in record %d: %s\n", i + 1, s);
    }

    fclose(f);

    return n_records;
}

t_record_vect get_vect_from_file_csv(char in [], t_record* month_p []) {
    t_record_vect out;

    unsigned long max_size = n_records_in_csv(in);

    out.vect = malloc(sizeof(t_record) * max_size);

    out.n = read_file_csv(in, out.vect, month_p);

    return out;
}