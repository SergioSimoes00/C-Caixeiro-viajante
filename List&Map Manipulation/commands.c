#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "commands.h"
#include "utils.h"

void loadp(PtList list){
    // Checks if the list has data already.
    if(!listIsEmpty(list)){
        printf("\nPatient data has already been loaded!\n");
        return;
    }

    // Ask for the file name.
    char filename[30];
	printf("\nPatients file name> ");
	fgets(filename, 30, stdin);
	int len = strlen(filename);
	if (len > 0 && filename[len - 1] == '\n') {
		filename[len - 1] = '\0';
	}

    FILE *f = NULL;

    f = fopen(filename, "r");

    if(f == NULL){
        printf("\nFile %s not found\n", filename);
        return;
    }

    char nextLine[1024];

    int countPatients = 0; // Patients count.
    bool firstLine = true;

    while(fgets(nextLine, sizeof(nextLine), f)){
        if(strlen(nextLine) < 1){
            continue;
        }

        // As the first line of the file contains the names of the fields it should be ignored.
        if(firstLine){
            firstLine = false;
            continue;
        }

        char **tokens = split(nextLine, 11, ";");

        //At this moment the tokens array is composed with the following "strings"
        //tokens[0] - id
        //tokens[1] - sex
        //tokens[2] - birth year
        //tokens[3] - country
        //tokens[4] - region
        //tokens[5] - infection reason
        //tokens[6] - infected by
        //tokens[7] - confirmed date
        //tokens[8] - released date
        //tokens[9] - deceased date
        //tokens[10] - status

        // Deals with empty information.
        for(int i = 1; i < 11; i++){
            if(*tokens[i] == '\0'){
                if(i == 2 || i == 6){
                    tokens[i] = "-1";
                }else if(i > 6 && i < 10){
                    tokens[i] = "0/0/0";
                }else{
                    tokens[i] = "";
                }
            }
        }
        
        // Initializes an instance of date.
        Date confirmed;
        if(tokens[7] == "0/0/0"){
            confirmed = dateCreate(0, 0, 0);
        }else{
            char** date = split(tokens[7], 3, "/");
            confirmed = dateCreate(atoi(date[0]), atoi(date[1]), atoi(date[2]));
        }

        // Initializes an instance of date.
        Date released;
        if(tokens[8] == "0/0/0"){
            released = dateCreate(0, 0, 0);
        }else{
            char** date = split(tokens[8], 3, "/");
            released = dateCreate(atoi(date[0]), atoi(date[1]), atoi(date[2]));
        }

        // Initializes an instance of date.
        Date deceased;
        if(tokens[9] == "0/0/0"){
            deceased = dateCreate(0, 0, 0);
        }else{
            char** date = split(tokens[9], 3, "/");
            deceased = dateCreate(atoi(date[0]), atoi(date[1]), atoi(date[2]));
        }

        long int infectedBy;
        if(tokens[6] == "-1"){
            infectedBy = -1;
        }else{
            char *ptr;
            infectedBy = strtol(tokens[6], &ptr, 10);
        }
        
        char *ptr2;
        Patient p = patientCreate(strtol(tokens[0], &ptr2, 10), tokens[1], atoi(tokens[2]), tokens[3],
                                    tokens[4], tokens[5], infectedBy, confirmed, released,
                                    deceased, tokens[10]);
        
        free(tokens); // Releases the alocated memory in function split.

        int error_code = listAdd(list, countPatients, p);

        if(error_code == LIST_FULL || error_code == LIST_INVALID_RANK ||
            error_code == LIST_NO_MEMORY || error_code == LIST_NULL){
            printf("\nAn error ocurred... Please try again... \n");
            return;
        }
        countPatients++;
    }
    printf("\n%d Patients were read!\n", countPatients);
    fclose(f);
}

void loadr(PtMap map){
    // Checks if the map has data already.
    if(!mapIsEmpty(map)){
        printf("\nRegion data has already been loaded!\n");
        return;
    }

    // Ask for the file name.
    char filename[30];
	printf("\nRegions file name> ");
	fgets(filename, 30, stdin);
	int len = strlen(filename);
	if (len > 0 && filename[len - 1] == '\n') {
		filename[len - 1] = '\0';
	}

    FILE *f = NULL;

    f = fopen(filename, "r");

    if(f == NULL){
        printf("\nFile %s not found\n", filename);
        return;
    }

    char nextLine[1024];

    int countRegions = 0; // Regions count.
    bool firstLine = true;

    while(fgets(nextLine, sizeof(nextLine), f)){
        if(strlen(nextLine) < 1){
            continue;
        }

        // As the first line of the file contains the names of the fields it should be ignored.
        if(firstLine){
            firstLine = false;
            continue;
        }

        char **tokens = split(nextLine, 4, ";");

        //At this moment the tokens array is composed with the following "strings"
        //tokens[0] - region
        //tokens[1] - city
        //tokens[2] - area
        //tokens[3] - population

        // Deals with commas in population.
        for(int i = 0, j; tokens[3][i] != '\0'; i++){
            if(tokens[3][i] == ','){
                for(j = i; tokens[3][j] != '\0'; j++){
                    tokens[3][j] = tokens[3][j+1];
                }
                tokens[3][j] = '\0';
            }
        }

        // Deals with commas in area.
        for(int i = 0; tokens[2][i] != '\0'; i++){
            if(tokens[2][i] == ','){
                tokens[2][i] = '.';
            }
        }

        Region r = regionCreate(tokens[0], tokens[1], atoi(tokens[3]), atof(tokens[2]));

        int error_code = mapPut(map, tokens[0], r);

        free(tokens); // Releases the alocated memory in function split.

        if(error_code == LIST_FULL || error_code == LIST_INVALID_RANK ||
            error_code == LIST_NO_MEMORY || error_code == LIST_NULL){
            printf("\nAn error ocurred... Please try again... \n");
            return;
        }
        countRegions++;
    }
    printf("\n%d Regions were read!\n", countRegions);
    fclose(f);
}

void clear(PtList list, PtMap map){
    // Checks if both collections are empty.
    if(listIsEmpty(list) && mapIsEmpty(map)){
        printf("\nThere is no loaded data to clear!\n");
        return;
    }

    int sizeList, sizeMap;
    listSize(list, &sizeList);
    mapSize(map, &sizeMap);

    if(mapIsEmpty(map)){    // If map is empty just clear the list.
        listClear(list);
        printf("\n%d records deleted from Patients List\n\n", sizeList);
    }else if(listIsEmpty(list)){    // If list is empty just clear the map.
        mapClear(map);
        printf("%d records deleted from Regions Map\n", sizeMap);
    }else{  // If both are not empty clear them.
        listClear(list);
        mapClear(map);
        printf("\n%d records deleted from Patients List\n\n", sizeList);
        printf("%d records deleted from Regions Map\n", sizeMap);
    }
}

void average(PtList list){
    // Checks if the list is empty.
    if(listIsEmpty(list)){
        printf("\nThe list is empty!\n");
        return;
    }

    float totalDeceased = 0;
    float totalDeceasedAges = 0;

    float totalReleased = 0;
    float totalReleasedAges = 0;

    float totalIsolated = 0;
    float totalIsolatedAges = 0;

    int sizeList;
    listSize(list, &sizeList);

    Patient p;

    for(int i = 0; i < sizeList; i++){
        listGet(list, i, &p);
        if(p.birthYear != -1){
            if(p.status[0] == 'd'){ // If patient status is deceased.
                totalDeceased++;
                totalDeceasedAges += calculateAge(2020, p.birthYear);
            }
            if(p.status[0] == 'r'){ // If patient status is released.
                totalReleased++;
                totalReleasedAges += calculateAge(2020, p.birthYear);
            }
            if(p.status[0] == 'i'){ // If patient status is isolated.
                totalIsolated++;
                totalIsolatedAges += calculateAge(2020, p.birthYear);
            }
        }
    }

    int deceasedAverage = round(totalDeceasedAges / totalDeceased);
    int releasedAverage = round(totalReleasedAges / totalReleased);
    int isolatedAverage = round(totalIsolatedAges / totalIsolated);

    printf("\nAverage Age for deceased patients: %d\n\n", deceasedAverage);
    printf("Average Age for released patients: %d\n\n", releasedAverage);
    printf("Average Age for isolated patients: %d\n", isolatedAverage);
}

void follow(PtList list){
    // Checks if the list is empty.
    if(listIsEmpty(list)){
        printf("\nThe list is empty!\n");
        return;
    }
    
    // Ask for patient id.
	long int id;
	printf("\nIntroduza o ID do paciente que quer dar FOLLOW> ");
	scanf("%ld", &id);

    // Checks if patient exists in the list.
    long int index = getPatientIndexByID(id, list);
    if(index < 0){
        printf("\nPlease insert a valid ID!\n");
        return;
    }
    
    Patient p;
    listGet(list, index, &p);
    printf("\nFollowing Patient: ID: %ld, SEX: %s, AGE: %d, COUNTRY/REGION: %s/%s, STATE: %s",
                                            p.id, p.sex, calculateAge(2020, p.birthYear),
                                            p.country, p.region, p.status);

    // While we can get the next patient info it keeps seraching.
    while(index > 0){
        index = getPatientIndexByID(p.infectedBy, list);
        if(index > 0){
            listGet(list, index, &p);
            printf("contaminated by Patient: ID: %ld, SEX: %s, AGE: %d, COUNTRY/REGION: %s/%s, STATE: %s",
                                            p.id, p.sex, calculateAge(2020, p.birthYear),
                                            p.country, p.region, p.status);
        }else if(index == -1){
            printf("contaminated by Unknown\n");
            break;
        }else{
            printf("contaminated by Patient: ID: %ld : does not exist record\n", p.infectedBy);
            break;
        }
    }
}

void sex(PtList list){
    // Checks if the list is empty.
    if(listIsEmpty(list)){
        printf("\nThe list is empty!\n");
        return;
    }

    float female = 0;
    float male = 0;
    float unknown = 0;

    int sizeList;
    listSize(list, &sizeList);

    Patient p;

    for(int i = 0; i < sizeList; i++){
        listGet(list, i, &p);
        if(p.sex[0] == 'f'){
            female++;
        }else if(p.sex[0] == 'm'){
            male++;
        }else{
            unknown++;
        }
    }

    int femalePercentage = round((female / sizeList) * 100);
    int malePercentage = round((male / sizeList) * 100);
    int unknownPercentage = round((unknown / sizeList) * 100);

    printf("\nPercentage of Females: %d%%\n", femalePercentage);
    printf("Percentage of Males: %d%%\n", malePercentage);
    printf("Percentage of unknown: %d%%\n", unknownPercentage);
    printf("Total of patients: %d\n", sizeList);
}

void show(PtList list){
    // Checks if the list is empty.
    if(listIsEmpty(list)){
        printf("\nThe list is empty!\n");
        return;
    }

    // Ask for patient id.
    long int id;
	printf("\nIntroduza o ID do paciente que quer dar SHOW> ");
	scanf("%ld", &id);

    // Check if patient exists in the list.
    long int index = getPatientIndexByID(id, list);
    if(index < 0){
        printf("\nPlease insert a valid ID!\n");
        return;
    }

    Patient p;
    listGet(list, index, &p);

    Date date = dateCreate(0, 0, 0);

    // Calculates the number of days that the patient is infected.
    int days = numberDaysInfected(p, list);

    // Calculates ag of the patient.
    int age = calculateAge(2020, p.birthYear);

    if(age == -1 && days == -1){
        printf("\nID: %ld\nSEX: %s\nAGE: unknown\nCOUNTRY/REGION: %s / %s\n", p.id, p.sex, p.country, p.region);
        printf("INFECTION REASON: %s\nSTATE: %sNUMBER OF DAYS WITH ILLNESS: unknown\n", p.infectionReason, p.status);
    }else if(days == -1){
        printf("\nID: %ld\nSEX: %s\nAGE: %d\nCOUNTRY/REGION: %s / %s\n", p.id, p.sex, age, p.country, p.region);
        printf("INFECTION REASON: %s\nSTATE: %sNUMBER OF DAYS WITH ILLNESS: unknown\n", p.infectionReason, p.status);
    }else if(age == -1){
        printf("\nID: %ld\nSEX: %s\nAGE: unknown\nCOUNTRY/REGION: %s / %s\n", p.id, p.sex, p.country, p.region);
        printf("INFECTION REASON: %s\nSTATE: %sNUMBER OF DAYS WITH ILLNESS: %d\n", p.infectionReason, p.status, days);
    }else{
        printf("\nID: %ld\nSEX: %s\nAGE: %d\nCOUNTRY/REGION: %s / %s\n", p.id, p.sex, age, p.country, p.region);
        printf("INFECTION REASON: %s\nSTATE: %sNUMBER OF DAYS WITH ILLNESS: %d\n", p.infectionReason, p.status, days);
    }
}

void oldest(PtList list){
    // Checks if the list is empty.
    if(listIsEmpty(list)){
        printf("\nThe list is empty!\n");
        return;
    }

    PtList females = listCreate(1);
    PtList males = listCreate(1);

    int sizeList;
    listSize(list, &sizeList);

    Patient p;

    int age;
    int fMaxAge = 0;
    int mMaxAge = 0;

    for(int i = 0; i < sizeList; i++){
        listGet(list, i, &p);
        if(p.birthYear != -1){
            age = calculateAge(2020, p.birthYear);
            if(p.sex[0] == 'f'){
                if(age == fMaxAge){ // If the patient age is equal to the current max, add it to list.
                    listAdd(females, 0, p);
                }
                if(age > fMaxAge){ // If the patient age is bigger to the current max, clear list and add it.
                    fMaxAge = age;
                    listClear(females);
                    listAdd(females, 0, p);
                }
            }if(p.sex[0] == 'm'){ 
                if(age == mMaxAge){ // If the patient age is equal to the current max, add it to list.
                    listAdd(males, 0, p);
                }
                if(age > mMaxAge){ // If the patient age is bigger to the current max, clear list and add it.
                    mMaxAge = age;
                    listClear(males);
                    listAdd(males, 0, p);
                }
            }
        }
    }

    int maleSize, femaleSize;
    listSize(males, &maleSize);
    listSize(females, &femaleSize);

    printf("\nFemales:\n");
    for(int i = 0; i < femaleSize; i++){
        listGet(females, i, &p);
        printf("ID: %ld, SEX: %s, AGE: %d, COUNTRY/REGION: %s/%s, STATE: %s",
                                            p.id, p.sex, calculateAge(2020, p.birthYear),
                                            p.country, p.region, p.status);
    }

    printf("\nMales:\n");
    for(int i = 0; i < maleSize; i++){
        listGet(males, i, &p);
        printf("ID: %ld, SEX: %s, AGE: %d, COUNTRY/REGION: %s/%s, STATE: %s",
                                            p.id, p.sex, calculateAge(2020, p.birthYear),
                                            p.country, p.region, p.status);
    }

    // Release the allocated memory of the two created lists in this function.
    listDestroy(&males);
    listDestroy(&females);
}

void matrix(PtList list){
    // Checks if the list is empty.
    if(listIsEmpty(list)){
        printf("\nThe list is empty!\n");
        return;
    }

    int sizeList;
    listSize(list, &sizeList);

    int matrix[6][3] = {0}; // Matrix with size 6 by 3 of integers.
    int age;
    Patient p;

    for(int i = 0; i < sizeList; i++){
        listGet(list, i, &p);
        if(p.birthYear != -1){
            age = calculateAge(2020, p.birthYear);
            if(age < 16){ // [0-15]
                if(p.status[0] == 'i')
                    matrix[0][0]++;
                if(p.status[0] == 'd')
                    matrix[0][1]++;
                if(p.status[0] == 'r')
                    matrix[0][2]++;
            }
            if(age > 15 && age < 31){ // [16-30]
                if(p.status[0] == 'i')
                    matrix[1][0]++;
                if(p.status[0] == 'd')
                    matrix[1][1]++;
                if(p.status[0] == 'r')
                    matrix[1][2]++;
            }
            if(age > 30 && age < 46){ // [31-45]
                if(p.status[0] == 'i')
                    matrix[2][0]++;
                if(p.status[0] == 'd')
                    matrix[2][1]++;
                if(p.status[0] == 'r')
                    matrix[2][2]++;
            }
            if(age > 45 && age < 61){ // [46-60]
                if(p.status[0] == 'i')
                    matrix[3][0]++;
                if(p.status[0] == 'd')
                    matrix[3][1]++;
                if(p.status[0] == 'r')
                    matrix[3][2]++;
            }
            if(age > 60 && age < 76){ // [61-75]
                if(p.status[0] == 'i')
                    matrix[4][0]++;
                if(p.status[0] == 'd')
                    matrix[4][1]++;
                if(p.status[0] == 'r')
                    matrix[4][2]++;
            }
            if(age > 75){ // [76...[
                if(p.status[0] == 'i')
                    matrix[5][0]++;
                if(p.status[0] == 'd')
                    matrix[5][1]++;
                if(p.status[0] == 'r')
                    matrix[5][2]++;
            }
        }
    }
    printf("\n\t\tIsolated\tDeceased\tReleased\n");
    printf("----------------------------------------------------------\n");
    printf("[0-15]\t\t%d\t\t%d\t\t%d\n", matrix[0][0], matrix[0][1], matrix[0][2]);
    printf("----------------------------------------------------------\n");
    printf("[16-30]\t\t%d\t\t%d\t\t%d\n", matrix[1][0], matrix[1][1], matrix[1][2]);
    printf("----------------------------------------------------------\n");
    printf("[31-45]\t\t%d\t\t%d\t\t%d\n", matrix[2][0], matrix[2][1], matrix[2][2]);
    printf("----------------------------------------------------------\n");
    printf("[46-60]\t\t%d\t\t%d\t\t%d\n", matrix[3][0], matrix[3][1], matrix[3][2]);
    printf("----------------------------------------------------------\n");
    printf("[61-75]\t\t%d\t\t%d\t\t%d\n", matrix[4][0], matrix[4][1], matrix[4][2]);
    printf("----------------------------------------------------------\n");
    printf("[76...[\t\t%d\t\t%d\t\t%d\n", matrix[5][0], matrix[5][1], matrix[5][2]);
}

void regions(PtMap map){
    // Checks if the map is empty.
    if(mapIsEmpty(map)){
        printf("\nThe map is empty!\n");
        return;
    }

    int size;
    mapSize(map, &size);

    Region *regions = mapValues(map);

    Region r1, r2;
    for(int i = 0; i < size; i++){ // Bubble sort algorithm.
        for(int j = 0; j < size-i-1; j++){
            r1 = regions[j];
            r2 = regions[j+1];
            if(strcmp(r1.name, r2.name) > 0){
                regions[j] = r2;
                regions[j+1] = r1;
            }
        }
    }
    
    printf("\n");
    for(int i = 0; i < size; i++){
        regionPrint(regions[i]);
        printf("\n");
    }

    free(regions);
}