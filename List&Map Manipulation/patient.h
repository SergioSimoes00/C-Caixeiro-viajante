#pragma once

#include "date.h"

typedef struct patient{
    long int id;                // ID
    char sex[6];                // Gender
    int birthYear;              // Year of birth.
    char country[40];           // Country
    char region[40];            // Region
    char infectionReason[100];  // Why he was infected
    long int infectedBy;        // Who infected him
    Date confirmedDate;         // Date of infection confirmation
    Date releasedDate;          // Date of infection cleared
    Date deceasedDate;          // Date of death
    char status[10];            // State that he is in
} Patient;

/**
 * @brief Creates an instance of patient with the given parameters.
 * 
 * @param id [in] ID.
 * @param sex [in] Gender.
 * @param birthYear [in] Year of birth.
 * @param country [in] Country.
 * @param region [in] Region.
 * @param infectionReason [in] Why he was infected.
 * @param infectedBy [in] Who infected him.
 * @param confirmedDate [in] Date of infection confirmation.
 * @param releasedDate [in] Date of infection cleared.
 * @param deceasedDate [in] Date of death.
 * @param status [in] State that he is in.
 * @return Patient Instance of patient.
 */
Patient patientCreate(long int id, char *sex, int birthYear, char *country, char *region,
                        char *infectionReason, long int infectedBy, Date confirmedDate, Date releasedDate,
                        Date deceasedDate, char *status);

/**
 * @brief Prints information about a given patient to the console.
 * 
 * @param patient [in] Patient to get information from.
 */
void patientPrint(Patient patient);