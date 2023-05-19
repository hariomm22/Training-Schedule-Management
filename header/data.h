#ifndef DATA_H
#define DATA_H

typedef struct admin
{
    char userName[30];
    char password[20];
}Admin;


typedef struct faculty
{ 
    char technologyName[30];
    char facultyName[30];
    char userName[30];
    char password[30];
}Faculty;



typedef struct training
{ 
    long int batchId;
    char technology[30];
    char startDate[30];
    int noOfDays;
    char endDate[30];
    char venueDetail[30];
    int noOfParticipants;
    char month[30];
}Training;

typedef struct facultyAssignments 
{ 
    long int batchId;
    char technology[30];
    char startDate[30];
    int noOfDays;
    char endDate[30];
    char venueDetail[30];
    int noOfParticipants;
    char month[30];
    char facultyEmail[30];
    char status[30]; 
}FacultyAssignments;

#endif