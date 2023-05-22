#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../header/date.h"
// use time.h header
char* strptime(const char* __restrict, const char* __restrict, struct tm* __restrict);

// this function check date is valid or not if date is valid then function return true  else return false
bool checkDateFormat(char *date){
    int days,month,year;
    sscanf(date,"%d/%d/%d",&days,&month,&year); // getting day month year in int formate from date string
    if(year<0 || year>99){
        return false;
    }
    if(month<1 || month >12){
        return false;
    }
    int dayOfMonth;
    switch(month){
        case 2:
            dayOfMonth = (year%4==0)?29:28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            dayOfMonth=30;
            break;
        default:
            dayOfMonth=31;
            break;
    }
    if(days<1 || days>dayOfMonth){
        return false;
    }
    return true;
}


// this function calculate endDate from startDate and number of days


char* getEndDate(const char* startDate, int numDays) {
    struct tm start_date = {0};
    if (sscanf(startDate, "%d/%d/%d",
               &start_date.tm_mday, &start_date.tm_mon, &start_date.tm_year) != 3) {
        fprintf(stderr, "Invalid start date format\n");
        return NULL;
    }
    start_date.tm_mon -= 1;
    start_date.tm_year += 100;
    if (start_date.tm_year < 70)
        start_date.tm_year += 100;
    time_t start_time = mktime(&start_date);
    time_t new_time = start_time + (numDays * 24 * 60 * 60);
    struct tm* new_date = localtime(&new_time);
    char* endDate = malloc(sizeof(char) * 9);
    strftime(endDate, 9, "%d/%m/%y", new_date);
    return endDate;
}




// this function generate and return month from startDate 
char* getMonth(char* startDate)
{
    struct tm date = {0};
    strptime(startDate, "%d/%m/%y", &date);
    char* month_names[] = {
        "January", "February", "March", "April", "May", "June", "July",
        "August", "September", "October", "November", "December"
    };

    return month_names[date.tm_mon];
}
