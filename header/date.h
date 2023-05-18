#include<stdbool.h>
#ifndef DATE_H
#define DATE_H

void facultyMenu();
bool checkDateFormat(char*);
char* getEndDate(const char* , int );
char* getMonth(char*);
#endif