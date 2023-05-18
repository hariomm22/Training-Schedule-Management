#include <stdio.h>
// #include <stdbool.h>
#include <string.h>
#include "../../header/data.h"
#include "../../header/adminService.h"
#include "../../header/batchId.h"
#include "../../header/date.h"

int adminLogin(){
    Admin admin;
    printf("\n          *** Admin Login ***\n");
    printf("\nEnter username: ");
    scanf(" %[^\n]s",admin.userName);
    printf("Enter Password: ");
    scanf(" %[^\n]s",admin.password);
    if(strcmp(admin.userName,"Admin")==0 && strcmp(admin.password,"Wipro@123")==0){
        return 1;
    }else{
        return 0;
    }
}

void addNewFaulty(){
    //../../db-files/
    FILE* file = fopen("db-files/facultyInfo.txt", "a"); 
    Faculty faculty;
    printf("\n          *** Add New Faculty ***\n");
    printf("\nEnter Faculty Name: ");
    scanf(" %[^\n]s",faculty.facultyName);
    printf("Enter Technology Name: ");
    scanf(" %[^\n]s",faculty.technologyName);
    printf("Enter unique userName: ");
    scanf("%s",faculty.userName);
    printf("Enter Password: ");
    scanf(" %[^\n]s",faculty.password);
    if (file != NULL) {
        // fwrite(&faculty, sizeof(faculty), 1, file);
        fprintf(file,"%s,%s,%s,%s\n",faculty.facultyName,faculty.technologyName,faculty.userName,faculty.password);
        fclose(file);
        printf("\n\t\tData inserted successfully.\n");
    } else {
        printf("\n\t\tUnable to open the file.\n");
    }
}


void createNewTraining(){
    //../../db-files/
    FILE* file = fopen("db-files/trainingInfo.txt", "a"); 
    Training training;
    printf("\n          *** create New training ***\n");
    training.batchId=getBatchId();
    printf("Enter Technology Name: ");
    scanf(" %[^\n]s",training.technology);
    printf("Enter startDate of trainnig (dd/mm/yy): ");
    scanf(" %[^\n]s",training.startDate);
    while(!checkDateFormat(training.startDate)){
        printf("\n\t Invalid date Format please enter again\n\n");
        printf("Enter startDate of trainnig (dd/mm/yy): ");
        scanf(" %[^\n]s",training.startDate);
    }
    strcpy(training.month, getMonth(training.startDate)); // get month form startDate
    printf("Enter no of Days training: ");
    scanf("%d",&training.noOfDays);
    strcpy(training.endDate, getEndDate(training.startDate,training.noOfDays)); // get traing endmonth from startdate
    printf("Enter no of Participants: ");
    scanf("%d",&training.noOfParticipants);
    printf("Enter the venueDetails : ");
    scanf(" %[^\n]s",training.venueDetail);
  
    if (file != NULL) {
        // fwrite(&faculty, sizeof(faculty), 1, file);
        fprintf(file,"%ld,%s,%s,%d,%s,%s,%d,%s\n",training.batchId,training.technology,
        training.startDate,training.noOfDays,training.endDate,training.venueDetail,
        training.noOfParticipants,training.month);
        fclose(file);
        printf("\n\t\tData inserted successfully.\n");
    } else {
        printf("\n\t\tUnable to open the file.\n");
    }
}