typedef struct {
    unsigned short year;
    unsigned char mounth;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    char temp;
} time_temp;

char t_average_mount(unsigned long n, time_temp a [], unsigned short year, unsigned char mount);

char t_min_mounth(unsigned long n, time_temp a [], unsigned short year, unsigned char mount);

char t_max_mounth(unsigned long n, time_temp a [], unsigned short year, unsigned char mount);

char t_average_year(unsigned long n, time_temp a [], unsigned short year);

char t_min_year(unsigned long n, time_temp a [], unsigned short year);

char t_max_year(unsigned long n, time_temp a [], unsigned short year);