#pragma once

typedef struct date{
    unsigned int day, month, year; // Day, month, year.
} Date;

/**
 * @brief Creates an instance of date.
 * 
 * @param day [in] Day.
 * @param month [in] Month.
 * @param year [in] Year.
 * @return Date Instance of date.
 */
Date dateCreate(unsigned int day, unsigned int month, unsigned int year);

/**
 * @brief Prints information of a given date to the console.
 * 
 * @param date [in] Date to get information from.
 */
void datePrint(Date date);

/**
 * @brief Compares if a date is after, equal or before another date.
 * 
 * @param date1 [in] Date to compare.
 * @param date2 [in] Date to compare.
 * @return int Returns 1 if date1 is after date2, -1 if date1 is before date2 or 0 if they are equal.
 */
int dateCompare(Date date1, Date date2);

/**
 * @brief Calculates the number of days between two dates.
 * 
 * @param date1 [in] Date to compare.
 * @param date2 [in] Date to compare.
 * @return int Number of days between two dates.
 */
int dateDaysDifference(Date date1, Date date2);