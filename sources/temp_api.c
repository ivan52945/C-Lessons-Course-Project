#include <math.h>
#include <stdio.h>

#include "../headers/temp_api.h"

/**
 * @brief Calculates average temperature from records
 *
 * Computes arithmetic mean of all temperature values in the array.
 * Uses rounding to nearest integer for final result.
 *
 * @param n_rec Number of valid records in array
 * @param a Array of temperature records
 * @return Average temperature in °C (rounded), or -120 if no records
 */
char t_average(unsigned long n_rec, t_record_t a[])
{
    long long sum = 0;
    char average;

    for (int i = 0; i < n_rec; i++)
        sum += a[i].temp;

    average = (n_rec > 0) ? round(sum * 1.0 / n_rec) : -120;

    return average;
}

/**
 * @brief Finds minimum temperature in records
 *
 * Scans all records to determine coldest temperature.
 *
 * @param n_rec Number of valid records
 * @param a Array of temperature records
 * @return Minimum temperature in °C, or 120 if no records
 */
char t_min(unsigned long n_rec, t_record_t a[])
{
    char min = 120;

    for (int i = 0; i < n_rec; i++) {
        min = (min > a[i].temp) ? a[i].temp : min;
    }

    return min;
}

/**
 * @brief Finds maximum temperature in records
 *
 * Scans all records to determine hottest temperature.
 *
 * @param n_rec Number of valid records
 * @param a Array of temperature records
 * @return Maximum temperature in °C, or -120 if no records
 */
char t_max(unsigned long n_rec, t_record_t a[])
{
    char max = -120;

    for (int i = 0; i < n_rec; i++)
        max = (max < a[i].temp) ? a[i].temp : max;

    return max;
}

/**
 * @brief Calculates average temperature for specified month
 *
 * @param n_rec Total number of records (unused, kept for interface consistency)
 * @param a Complete records array (unused)
 * @param month Target month (1-12, where 1=January)
 * @param month_vect Pre-calculated month index vectors
 * @return Average temperature in °C (rounded), -120 if no data for month
 *
 * @note Returns -120 (error code) when month has no records
 * @see t_average() Called for actual calculation
 */
char t_average_mount(unsigned long n_rec, t_record_t a[], int month, t_record_vect_t month_vect[])
{
    t_record_vect_t mnt_s = month_vect[month - 1];

    if (mnt_s.n)
        return  t_average(mnt_s.n, mnt_s.vect);
    else
        return -120;
}

/**
 * @brief Finds minimum temperature for specified month
 *
 * @param n_rec Total record count (unused)
 * @param a Full dataset (unused)
 * @param month Target month (1-12)
 * @param month_vect Month index structure
 * @return Lowest temperature in °C, -120 if no data
 *
 * @warning Month must be 1-12 (no validation)
 * @see t_min() Called for actual calculation
 */
char t_min_month(unsigned long n_rec, t_record_t a[], int month, t_record_vect_t month_vect[])
{
    t_record_vect_t mnt_s = month_vect[month - 1];

    if (mnt_s.n)
        return t_min(mnt_s.n, mnt_s.vect);
    else
        return -120;
}

/**
 * @brief Finds maximum temperature for specified month
 *
 * @param n_rec Total records (unused)
 * @param a All records (unused)
 * @param month Target month (1-12)
 * @param month_vect Month index data
 * @return Highest temperature in °C, -120 if no data
 *
 * @note Consistent error code (-120) with other month functions
 * @see t_max() Called for core logic
 */
char t_max_month(unsigned long n_rec, t_record_t a[], int month, t_record_vect_t month_vect[])
{
    t_record_vect_t mnt_s = month_vect[month - 1];

    if (mnt_s.n)
        return t_max(mnt_s.n, mnt_s.vect);
    else
        return -120;
}

/**
 * @brief Calculates yearly average temperature
 *
 * Wrapper for t_average() that provides consistent yearly statistics interface.
 *
 * @param n_rec Number of valid temperature records
 * @param a Array of temperature records
 * @return Average annual temperature in °C (rounded), -120 if no records
 */
char t_average_year(unsigned long n_rec, t_record_t a[])
{
    return t_average(n_rec, a);
}

/**
 * @brief Finds yearly minimum temperature
 *
 * Wrapper for t_min() providing consistent yearly statistics interface.
 *
 * @param n_rec Number of valid records
 * @param a Array of temperature records
 * @return Coldest temperature in °C, 120 if no records
 *
 * @note Directly calls t_min() with same parameters
 * @see t_min() Core minimum calculation function
 */
char t_min_year(unsigned long n_rec, t_record_t a[])
{
    return t_min(n_rec, a);
}

/**
 * @brief Finds yearly maximum temperature
 *
 * Wrapper for t_max() providing consistent yearly statistics interface.
 *
 * @param n_rec Number of valid records
 * @param a Array of temperature records
 * @return Hottest temperature in °C, -120 if no records
 *
 * @note Directly calls t_max() with same parameters
 * @see t_max() Core maximum calculation function
 */
char t_max_year(unsigned long n_rec, t_record_t a[])
{
    return t_max(n_rec, a);
}

/**
 * @brief Prints formatted monthly temperature statistics
 *
 * Displays table with calculated average, minimum and maximum temperatures
 * for specified month. Only shows data if month exists in records.
 *
 * @param n_rec Total number of records (passed to calculation functions)
 * @param a Complete array of temperature records
 * @param month Target month (1-12)
 * @param month_vect Pre-built month index vectors
 *
 * @note Uses t_average_month(), t_min_month(), t_max_month()
 * @warning Month parameter must be 1-12 (no validation)
 * @see print_year_statistics() For annual report version
 */
void print_month_statistics(unsigned long n_rec, t_record_t a[], int month, t_record_vect_t month_vect[])
{
    if (month_vect[month].vect) {
        int t_average = t_average_mount(n_rec, a, month, month_vect);
        int t_min = t_min_month(n_rec, a, month, month_vect);
        int t_max = t_max_month(n_rec, a, month, month_vect);

        printf("Month  Average  Minimal  Maximal\n");
        printf("%3d      %3d      %3d      %3d\n", month, t_average, t_min, t_max);
    }
    else
        printf("There are no data for month %d", month);
}

/**
 * @brief Prints comprehensive annual temperature report
 *
 * Generates:
 * 1. Monthly statistics table (all months with data)
 * 2. Yearly aggregate statistics (average/min/max)
 *
 * @param n_rec Total valid records count
 * @param a Array of all temperature records
 * @param month_vect Month index vectors (length 12)
 *
 * @note Uses both monthly and yearly calculation functions
 * @warning month_vect must be properly initialized
 */
void print_year_statistics(unsigned long n_rec, t_record_t a[], t_record_vect_t month_vect[])
{
    printf("Month  Average  Minimal  Maximal\n");
    for (int i = 1; i <= 12; i++)
        if (month_vect[i].vect) {
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