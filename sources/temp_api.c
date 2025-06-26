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
 * @param month Target month (1-12, where 1=January)
 * @param month_vect Pre-calculated month index vectors
 * @return Average temperature in °C (rounded), -120 if no data for month
 *
 * @note Returns -120 (error code) when month has no records
 * @see t_average() Called for actual calculation
 */
char t_average_mount(int month, t_record_vect_t month_vect[])
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
 * @param month Target month (1-12)
 * @param month_vect Month index structure
 * @return Lowest temperature in °C, -120 if no data
 *
 * @warning Month must be 1-12 (no validation)
 * @see t_min() Called for actual calculation
 */
char t_min_month(int month, t_record_vect_t month_vect[])
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
 * @param month Target month (1-12)
 * @param month_vect Month index data
 * @return Highest temperature in °C, -120 if no data
 *
 * @note Consistent error code (-120) with other month functions
 * @see t_max() Called for core logic
 */
char t_max_month(int month, t_record_vect_t month_vect[])
{
    t_record_vect_t mnt_s = month_vect[month - 1];

    if (mnt_s.n)
        return t_max(mnt_s.n, mnt_s.vect);
    else
        return -120;
}

/**
 * @brief Calculates average temperature for yearly data
 *
 * Wrapper that computes arithmetic mean temperature
 * from pre-aggregated yearly records.
 *
 * @param year_vect Yearly data container with records
 * @return Average temperature in °C (rounded), -120 if no data
 *
 * @note Simply delegates to t_average() function
 * @see t_average() Actual calculation implementation
 */
char t_average_year(t_record_vect_t year_vect)
{
    return t_average(year_vect.n, year_vect.vect);
}

/**
 * @brief Finds minimum temperature in yearly data
 *
 * Wrapper that determines coldest temperature
 * from pre-aggregated yearly records.
 *
 * @param year_vect Yearly data container with records
 * @return Minimum temperature in °C, 120 if no data
 *
 * @note Delegates to t_min() function
 * @see t_min() Core minimum calculation
 */
char t_min_year(t_record_vect_t year_vect)
{
    return t_min(year_vect.n, year_vect.vect);
}

/**
 * @brief Finds maximum temperature in yearly data
 *
 * Wrapper that determines hottest temperature
 * from pre-aggregated yearly records.
 *
 * @param year_vect Yearly data container with records
 * @return Maximum temperature in °C, -120 if no data
 *
 * @note Delegates to t_max() function
 * @see t_max() Core maximum calculation
 */
char t_max_year(t_record_vect_t year_vect)
{
    return t_max(year_vect.n, year_vect.vect);
}

/**
 * @brief Prints temperature statistics for specified month
 *
 * Displays formatted table with calculated average, minimum
 * and maximum temperatures for given month.
 *
 * @param month Target month (1-12)
 * @param month_vect Array of monthly data vectors
 *
 * @note Only prints data if records exist for the month
 * @warning Month parameter must be 1-12 (no validation)
 * @see print_year_statistics() For annual report
 */
void print_month_statistics(int month, t_record_vect_t month_vect[])
{
    if (month_vect[month].vect) {
        int t_average = t_average_mount(month, month_vect);
        int t_min = t_min_month(month, month_vect);
        int t_max = t_max_month(month, month_vect);

        printf("Month  Average  Minimal  Maximal\n");
        printf("%3d      %3d      %3d      %3d\n", month, t_average, t_min, t_max);
    }
    else
        printf("There are no data for month %d", month);
}

/**
 * @brief Prints complete yearly temperature report
 *
 * Generates:
 * 1. Monthly statistics table (all months with data)
 * 2. Summary section with yearly aggregates
 *
 * @param year_vect Container with yearly temperature data
 * @param month_vect Array of monthly data vectors
 *
 * @note Uses t_average_year(), t_min_year(), t_max_year()
 * @code
 * // Usage:
 * print_year_statistics(year_data, month_index);
 * @endcode
 */
void print_year_statistics(t_record_vect_t year_vect, t_record_vect_t month_vect[])
{
    printf("Month  Average  Minimal  Maximal\n");
    for (int i = 1; i <= 12; i++)
        if (month_vect[i].vect) {
            int t_average = t_average_mount(i, month_vect);
            int t_min = t_min_month(i, month_vect);
            int t_max = t_max_month(i, month_vect);
            printf("%3d\t%3d\t %3d\t  %3d\n", i, t_average, t_min, t_max);
        }

    int t_average = t_average_year(year_vect);
    int t_min = t_min_year(year_vect);
    int t_max = t_max_year(year_vect);

    printf("average temperature in year is %d degrees C\n", t_average);
    printf("minimal temperature in year is %d degrees C\n", t_min);
    printf("maximal temperature in year is %d degrees C\n", t_max);
}