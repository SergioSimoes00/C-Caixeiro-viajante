#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "patient.h"

Date findNewestDate(PtList list);

void toLowerCase(char str[]) {
    for(int i = 0; str[i]; i++){
		str[i] = (char)tolower(str[i]);
	}
}

int equalsStringIgnoreCase(char str1[], char str2[]) {
    char s1[30];
	char s2[30];
	strcpy(s1, str1);
	strcpy(s2, str2);
	toLowerCase(s1);
	toLowerCase(s2);
	return (strcmp(s1, s2) == 0);
}

char** split(char *string, int nFields, const char *delim) {
    char **tokens = (char**) malloc(sizeof(char*) * nFields);
    int index = 0;
    int len = strlen(string);
    tokens[index++] = &string[0];
    for(int i=0; i < len; i++) {
        if( string[i] == delim[0] ) {
            string[i] = '\0';
            if( i < len - 1 ) {
                tokens[index++] = &string[i] + 1;
            }           
        }
    }
    return tokens;
}

int calculateAge(int currYear, int birthYear){
    if(birthYear == -1 || birthYear > currYear) return -1;
    return currYear - birthYear;
}

long int getPatientIndexByID(long int id, PtList list){
    if(id == -1) return -1;

    long int index = -2;
    Patient p;
    int size;
    listSize(list, &size);

    for(int i = 0; i < size; i++){
        listGet(list, i, &p);
        if(p.id == id){
            index = i;
        }
    }
    return index;
}

Date findNewestDate(PtList list){
    int size;
    listSize(list, &size);

    Date newDate = dateCreate(0, 0, 0);

    Date d;
    Patient p;
    for(int i = 0; i < size; i++){
        listGet(list, i, &p);
        d = p.confirmedDate;
        if(dateCompare(d, newDate) == 1){
            newDate.day = d.day;
            newDate.month = d.month;
            newDate.year = d.year;
        }
    }
    return newDate;
}

int numberDaysInfected(Patient p, PtList list){
    Date date = dateCreate(0, 0, 0);

    int days = -1;
    
    if(p.status[0] == 'r'){
        if(dateCompare(p.confirmedDate, date) == 1 && dateCompare(p.releasedDate, date) == 1){
            days = dateDaysDifference(p.confirmedDate, p.releasedDate);
        }
    }else if(p.status[0] == 'd'){
        if(dateCompare(p.confirmedDate, date) == 1 && dateCompare(p.deceasedDate, date) == 1){
            days = dateDaysDifference(p.confirmedDate, p.deceasedDate);
        }
    }else{
        if(dateCompare(p.confirmedDate, date) == 1){
            Date lastDate = findNewestDate(list);
            days = dateDaysDifference(p.confirmedDate, lastDate);
        }
    }
    return days;
}