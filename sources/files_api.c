#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/t_record_type.h"
#include "../headers/files.h"

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

int read_file_csv(char in [], t_record a [], t_record* month_start []) {
    int n = 0;
    char s[30];
    FILE* f = open_file(in, "r");
    int readed;
    t_record tmp;
    int n_correct;

    while((readed = fscanf(f, "%[^\n]\n", s)) != EOF) {

        n_correct = sscanf(s, "%hu;%hhu;%hhu;%hhu;%hhu;%hhd", &(tmp.year), &(tmp.mounth), &(tmp.day), &(tmp.hour), &(tmp.minute), &(tmp.temp));

        if(n_correct == 6) {
            if((tmp.mounth > 0 && tmp.mounth < 13) && !month_start[tmp.mounth - 1]) {
                month_start[tmp.mounth - 1] = a + n;
            }
            a[n++] = tmp;
        }
        else
            printf("Wrong data in record %d: %s\n", n + 1, s);
    }

    return n;

    fclose(f);
}