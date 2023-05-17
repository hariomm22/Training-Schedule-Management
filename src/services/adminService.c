#include <stdio.h>
// #include <stdbool.h>
#include <string.h>
#include "../../header/data.h"
#include "../../header/adminService.h"
#include "../../header/batchId.h"

int adminLogin(){
    Admin admin;
    printf("\n          *** Admin Login ***\n");
    printf("\nEnter username: ");
    scanf("%s",admin.userName);
    printf("Enter Password: ");
    scanf("%s",admin.password);
   
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
    scanf("%s",faculty.facultyName);
    printf("Enter Technology Name: ");
    scanf("%s",faculty.technologyName);
    printf("Enter unique userName: ");
    scanf("%s",faculty.userName);
    printf("Enter Password: ");
    scanf("%s",faculty.password);
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
    scanf("%s",training.technology);
    printf("Enter startDate of trainnig (dd/mm/yy): ");
    scanf("%s",training.startDate);
    printf("Enter no of Days training: ");
    scanf("%d",&training.noOfDays);
     printf("Enter no of Participants: ");
    scanf("%d",&training.noOfParticipants);
    printf("Enter the venueDetails : ");
    scanf("%s",training.venueDetail);
    printf("Enter the months which training started : ");
    scanf("%s",training.month);
    printf("Enter endDate of trainnig (dd/mm/yy) : ");
    scanf("%s",training.endDate);
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