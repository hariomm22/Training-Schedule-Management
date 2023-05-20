#include <stdbool.h>
#include "data.h"
#ifndef FACULTYSERVICE_H
#define FACULTYSERVICE_H
bool isUserNamePresent(char * );
bool facultyLogin(char *userName , char *password);
Faculty getLogInedFaculty(char *userName);
FacultyAssignmentsList* getScheduleDetails(char *);
void insertFacultyAssignmentsInFacultyAssignmentsList(FacultyAssignmentsList** , FacultyAssignmentsList**,FacultyAssignmentsList*);
void facultyAssignmentsDisplay(FacultyAssignments);
bool requestToCancelAllocatedSchedule(long int  , char *);
#endif