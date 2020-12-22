#include <stdio.h>
#include "date.h"

int countLeapYears(Date d);

Date dateCreate(unsigned int day, unsigned int month, unsigned int year){
    Date date;
    date.day = day;
    date.month = month;
    date.year = year;
    return date;
}

void datePrint(Date date){
    printf("%02d/%02d/%04d", date.day, date.month, date.year);
}

int dateCompare(Date date1, Date date2){
    if(date1.year > date2.year){
        return 1;
    }else if(date1.year < date2.year){
        return -1;
    }else{
        if(date1.month > date2.month){
            return 1;
        }else if(date1.month < date2.month){
            return -1;
        }else{
            if(date1.day > date2.day){
                return 1;
            }else if(date1.day < date2.day){
                return -1;
            }else{
                return 0;
            }
        }
    }
}
  
int countLeapYears(Date d){ 
    int years = d.year; 
    if (d.month <= 2){
        years--;
    }
    return years / 4 - years / 100 + years / 400;
} 
  
int dateDaysDifference(Date date1, Date date2){
    const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    long int n1 = date1.year*365 + date1.day;
    for (int i=0; i<date1.month - 1; i++){
        n1 += monthDays[i];
    }
    n1 += countLeapYears(date1);
  
    long int n2 = date2.year*365 + date2.day;
    for (int i=0; i<date2.month - 1; i++){
        n2 += monthDays[i];
    }
    n2 += countLeapYears(date2);

    return (n2 - n1); 
}