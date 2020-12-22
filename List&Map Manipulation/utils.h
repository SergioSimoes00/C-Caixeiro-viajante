#pragma once

#include "list.h"

/**
 * @brief Turns all chars in a string to lower case.
 * 
 * @param str [in] String to turn lowercase.
 */
void toLowerCase(char str[]);


/**
 * @brief Compares two strings regardless of capitalization.
 * 
 * @param str1 [in] String to compare.
 * @param str2 [in] Dtring to compare.
 * @return int Returns if strings are equal or not.
 */
int equalsStringIgnoreCase(char str1[], char str2[]);

/**
 * @brief Devides a string into substrings separated by a given delimiter.
 * 
 * @param string [in] The string to devide.
 * @param nFields [in] Number of divisions.
 * @param delim [in] The substring delimiter.
 * @return char** Returns an array of the substrings.
 */
char** split(char *string, int nFields, const char *delim);

/**
 * @brief Calculates the age between two given years.
 * 
 * @param currYear [in] The current year.
 * @param birthYear [in] The birth year.
 * @return int Returns -1 if birthyear is -1 or if birthYear is bigger then currYear, else returns the age.
 */
int calculateAge(int currYear, int birthYear);

/**
 * @brief Get the patient index of a patient list given his id.
 * 
 * @param id [in] Id of the patient.
 * @param list [in] The list to search in.
 * @return long int Returns -2 if patient is not in the list, or -1 if the id is -1 else returns the index of the patient.
 */
long int getPatientIndexByID(long int id, PtList list);

/**
 * @brief Calculates the number of days a patient from a list of patients was infected.
 * 
 * @param p [in] Patient.
 * @param list [in] List to get patient information from.
 * @return int Number of days infected.
 */
int numberDaysInfected(Patient p, PtList list);