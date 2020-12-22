#include <stdio.h>
#include <string.h>
#include "patient.h"

Patient patientCreate(long int id, char sex[6], int birthYear, char country[40], char region[40],
                        char infectionReason[100], long int infectedBy, Date confirmedDate, Date releasedDate,
                        Date deceasedDate, char status[10]){
    Patient patient;
    patient.id = id;
    strcpy(patient.sex, sex);
    patient.birthYear = birthYear;
    strcpy(patient.country, country);
    strcpy(patient.region, region);
    strcpy(patient.infectionReason, infectionReason);
    patient.infectedBy = infectedBy;
    patient.confirmedDate = confirmedDate;
    patient.releasedDate = releasedDate;
    patient.deceasedDate = deceasedDate;
    strcpy(patient.status, status);
    return patient;
}

void patientPrint(Patient patient){
    printf("%ld | %s | %d | %s | %s | %s | %ld | ", patient.id, patient.sex, patient.birthYear,
                                                    patient.country, patient.region,
                                                    patient.infectionReason, patient.infectedBy);
    datePrint(patient.confirmedDate);
    printf(" | ");
    datePrint(patient.releasedDate);
    printf(" | ");
    datePrint(patient.deceasedDate);
    printf(" | %s", patient.status);
}