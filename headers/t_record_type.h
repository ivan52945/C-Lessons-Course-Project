#pragma once

/**
 * @struct t_record_t
 * @brief Temperature measurement record with timestamp components
 *
 * Stores a single temperature reading with decomposed timestamp information.
 * Suitable for systems requiring human-readable time components.
 */
typedef struct {
    unsigned short year;   ///< Measurement year (e.g., 2023)
    unsigned char month;   ///< Month (1-12, 1=January)
    unsigned char day;     ///< Day of month (1-31)
    unsigned char hour;    ///< Hour in 24h format (0-23)
    unsigned char minute;  ///< Minute (0-59)
    char temp;             ///< Temperature in °C (signed byte, -128 to +127)
} t_record_t;

/**
 * @struct t_record_vect_t
 * @brief Dynamic array of temperature records
 *
 * Represents a resizable collection of temperature measurements.
 * Manages both the storage buffer and its current capacity.
 */
typedef struct {
    t_record_t* vect;      ///< Pointer to dynamically allocated array of records
    unsigned long n;       ///< Current number of valid records in the array
} t_record_vect_t;