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

int read_file_csv(char in [], t_record a [], t_record* month_p []) {
    int n = 0;
    char s[30];
    FILE* f = open_file(in, "r");
    t_record tmp;
    int n_correct;

    for(int i = 0; fscanf(f, "%[^\n]\n", s) != EOF; i++) {

        n_correct = sscanf(s, "%hu;%hhu;%hhu;%hhu;%hhu;%hhd", &(tmp.year), &(tmp.month), &(tmp.day), &(tmp.hour), &(tmp.minute), &(tmp.temp));

        if(n_correct == 6 && (tmp.month > 0 && tmp.month < 13)) {
            if(!month_p[tmp.month - 1]) {
                month_p[tmp.month - 1] = a + n;
            }
            a[n++] = tmp;
        }
        else
            printf("Wrong data in record %d: %s\n", i + 1, s);
    }

    return n;

    fclose(f);
}