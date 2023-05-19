#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../../header/data.h"
#include "../../header/adminService.h"
#include "../../header/batchId.h"
#include "../../header/date.h"
#include "../../header/facultyService.h"

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

void addNewFaculty(){
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
    while (isUserNamePresent(faculty.userName))
    {
        printf("\n\t %s userName is already exits..!\n\n",faculty.userName);
         printf("Enter unique userName: ");
        scanf("%s",faculty.userName);
    }
    
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

void updateTraining(){
    long int batchId;
    Training updatedTraining;
    printf("Enter the BatchId :");
    scanf("%ld",&batchId);
    if(isBatchIdPresent(batchId)){
    printf("\n          *** Updating training ***\n");
    updatedTraining.batchId=batchId;
    printf("Enter Technology Name: ");
    scanf(" %[^\n]s",updatedTraining.technology);
    printf("Enter startDate of trainnig (dd/mm/yy): ");
    scanf(" %[^\n]s",updatedTraining.startDate);
    while(!checkDateFormat(updatedTraining.startDate)){
        printf("\n\t Invalid date Format please enter again\n\n");
        printf("Enter startDate of trainnig (dd/mm/yy): ");
        scanf(" %[^\n]s",updatedTraining.startDate);
    }
    strcpy(updatedTraining.month, getMonth(updatedTraining.startDate)); // get month form startDate
    printf("Enter no of Days training: ");
    scanf("%d",&updatedTraining.noOfDays);
    strcpy(updatedTraining.endDate, getEndDate(updatedTraining.startDate,updatedTraining.noOfDays)); // get traing endmonth from startdate
    printf("Enter no of Participants: ");
    scanf("%d",&updatedTraining.noOfParticipants);
    printf("Enter the venueDetails : ");
    scanf(" %[^\n]s",updatedTraining.venueDetail);

    FILE *file = fopen("db-files/trainingInfo.txt", "r");
    FILE *tempFile = fopen("db-files/temp.txt", "w");  //

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
    }

    Training training;

    while (fscanf(file, "%ld,%[^,],%[^,],%d,%[^,],%[^,],%d,%[^\n]\n",
                  &(training.batchId), training.technology, training.startDate, &(training.noOfDays),
                  training.endDate, training.venueDetail, &(training.noOfParticipants), training.month) != EOF) {
        if (training.batchId == batchId) {
            fprintf(tempFile, "%ld,%s,%s,%d,%s,%s,%d,%s\n",
                    training.batchId, updatedTraining.technology, updatedTraining.startDate,
                    updatedTraining.noOfDays, updatedTraining.endDate, updatedTraining.venueDetail,
                    updatedTraining.noOfParticipants, updatedTraining.month);
        } else {
            fprintf(tempFile, "%ld,%s,%s,%d,%s,%s,%d,%s\n",
                    training.batchId, training.technology, training.startDate, training.noOfDays,
                    training.endDate, training.venueDetail, training.noOfParticipants, training.month);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("db-files/trainingInfo.txt");
    rename("db-files/temp.txt", "db-files/trainingInfo.txt");

}
}


void allocateTrainingToFaculty(){
    long int batchId;
    char userName[30];
    printf("\n          *** allocate Training To Faculty ***\n");
    printf("\nEnter the BatchId To Allocate To Tranier : ");
    scanf("%ld",&batchId);
    if(isBatchIdPresent(batchId)){
        printf("\nEnter the faculty email to assing the batch : ");
        scanf("%s",userName);
        if(isUserNamePresent(userName)){
            Training training;
            FacultyAssignments facultyAssignments;
            FILE * trianingFile = fopen("db-files/trainingInfo.txt","r");
            FILE * allocatedTrainingFile = fopen("db-files/allocatedTraining.txt","a");
            if(trianingFile==NULL || allocatedTrainingFile==NULL){
                printf("\n\t\t Error in File Opening..!!");
            } else{
                  while (fscanf(trianingFile, "%ld,%[^,],%[^,],%d,%[^,],%[^,],%d,%[^\n]\n",
                  &(training.batchId), training.technology, training.startDate, &(training.noOfDays),
                  training.endDate, training.venueDetail, &(training.noOfParticipants), training.month) != EOF) {
                if (training.batchId == batchId) {
                    facultyAssignments.batchId=batchId;
                    strcpy(facultyAssignments.technology,training.technology);
                    strcpy(facultyAssignments.startDate,training.startDate);
                    facultyAssignments.noOfDays=training.noOfDays;
                    strcpy(facultyAssignments.endDate,training.endDate);
                    strcpy(facultyAssignments.venueDetail,training.venueDetail);
                    facultyAssignments.noOfParticipants=training.noOfParticipants;
                    strcpy(facultyAssignments.month,training.month);
                    strcpy(facultyAssignments.facultyEmail,userName);
                    strcpy(facultyAssignments.status,"allocated");
                    fprintf(allocatedTrainingFile, "%ld,%s,%s,%d,%s,%s,%d,%s,%s,%s\n",
                    facultyAssignments.batchId, facultyAssignments.technology, facultyAssignments.startDate, facultyAssignments.noOfDays,
                    facultyAssignments.endDate, facultyAssignments.venueDetail, facultyAssignments.noOfParticipants, facultyAssignments.month
                    ,facultyAssignments.facultyEmail,facultyAssignments.status);
                }
              }
              fclose(trianingFile);
              fclose(allocatedTrainingFile);
              printf("\n\t\t Allocate schedule to faculty Successful\n\n");
              printf(" Batch Id : %ld\n",facultyAssignments.batchId);
              printf(" Technology : %s\n",facultyAssignments.technology);
              printf(" Start Date to Training : %s\n",facultyAssignments.startDate);
              printf(" Number of Days for Training : %d\n",facultyAssignments.noOfDays);
              printf(" End Date to Training : %s\n",facultyAssignments.endDate);
              printf(" Training Venue Details : %s\n",facultyAssignments.venueDetail);
              printf(" Number of participants in Training : %d\n",facultyAssignments.noOfParticipants);
              printf(" Month which training Start : %s\n",facultyAssignments.startDate);
              printf(" Trainer Email address : %s\n",facultyAssignments.facultyEmail);
              printf(" Training Current Status : %s\n",facultyAssignments.status);
            }

        }else{
            printf("\n\t\tFaculty not found with %s !!!",userName);
        }
    } else {
        printf("\n\t\t%ld BatchId is not found !!!",batchId);
    }
}

bool isBatchIdPresent(long int batchId){
     Training training;
     FILE* file = fopen("db-files/trainingInfo.txt", "r"); 
     if(file==NULL){
        return false;
     }
     while (fscanf(file,"%ld,%[^,],%[^,],%d,%[^,],%[^,],%d,%[^\n]\n"
     ,&training.batchId,training.technology,
        training.startDate,&training.noOfDays,training.endDate,training.venueDetail,
        &training.noOfParticipants,training.month) !=EOF)
     {

        // "%ld,%s,%s,%d,%s,%s,%d,%s\n"
        if(training.batchId==batchId){
            return true;
        }
     }
     fclose(file);
     return false;
     
}
