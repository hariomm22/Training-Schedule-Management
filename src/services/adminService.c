#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../../header/data.h"
#include "../../header/adminService.h"
#include "../../header/batchId.h"
#include "../../header/date.h"
#include "../../header/facultyService.h"
#define ADMIN_LOG_FILE "db-files/adminLoginCredentials.txt"
#define TRAINING_FILE "db-files/trainingInfo.txt"
#define ALLOCATED_TRAINING_FILE "db-files/allocatedTraining.txt"
#define FACULTY_FILE "db-files/facultyInfo.txt"
#define STRING_SIZE 30

/*this function take username and password from user and check it in
adminLoginCredentials.txt file if username and password matched then return 1 else 0 */
int adminLogin(){
    Admin admin;
    printf("\n          *** Admin Login ***\n");
    printf("\nEnter username: ");
    scanf(" %[^\n]s",admin.userName);
    printf("Enter Password: ");
    scanf(" %[^\n]s",admin.password);
    char userName[STRING_SIZE];
    char password[STRING_SIZE];
    FILE *file = fopen(ADMIN_LOG_FILE,"r");
    if(file==NULL){
        return 0;
    }   
    fscanf(file,"userName=%s\n",userName);
    fscanf(file,"password=%s\n",password);
    if(strcmp(admin.userName,userName)==0 && strcmp(admin.password,password)==0){
        return 1;
    }else{
        return 0;
    }
}

// this function is take faculty info from admin and store in facultyInfo.txt file
void addNewFaculty(){
    //../../db-files/
    FILE* file = fopen(FACULTY_FILE, "a"); 
    Faculty faculty;
    printf("\n\t\t*** Add New Faculty ***\n");
    printf("\nEnter Faculty Name: ");
    scanf(" %[^\n]s",faculty.facultyName);
    printf("Enter Technology Name: ");
    scanf(" %[^\n]s",faculty.technologyName);
    printf("Enter email address : ");
    scanf("%s",faculty.userName);
    // check entered email is already exits or not 
    while (isUserNamePresent(faculty.userName)) // isUserNamePresent function check given userName presence if exits then return true 
    {
        printf("\n\t %s Email is already exits..!\n\n",faculty.userName);
         printf("Enter unique Email: ");
        scanf("%s",faculty.userName);
    }
    
    printf("Enter Password: ");
    scanf(" %[^\n]s",faculty.password);
    if (file != NULL) {
        fprintf(file,"%s,%s,%s,%s\n",faculty.facultyName,faculty.technologyName,faculty.userName,faculty.password);
        fclose(file);
        printf("\n\t\tData inserted successfully.\n");
    } else {
        printf("\n\t\tUnable to open the file.\n");
    }
}

// this function is create new training schedule and store the data into trainingInfo.txt file
void createNewTraining(){
    //../../db-files/
    FILE* file = fopen(TRAINING_FILE, "a"); 
    Training training;
    printf("\n\t\t*** create New training ***\n\n");
    training.batchId=getBatchId();
    printf("Enter Technology Name: ");
    scanf(" %[^\n]s",training.technology);
    printf("Enter startDate of trainnig (dd/mm/yy): ");
    scanf(" %[^\n]s",training.startDate);
     // checkDateFormat function take startdate as string input and check entered date is valid or not 
    while(!checkDateFormat(training.startDate)){ 
        printf("\n\t Invalid date Format please enter again\n\n");
        printf("Enter startDate of trainnig (dd/mm/yy): ");
        scanf(" %[^\n]s",training.startDate);
    }
    strcpy(training.month, getMonth(training.startDate)); // getMonth function return month from startDate
    printf("Enter no of Days training: ");
    scanf("%d",&training.noOfDays);
    // getEndDate function generate and return endDate from startDate and noOfDate training going on
    printf("Enter no of Participants: ");
    strcpy(training.endDate, getEndDate(training.startDate,training.noOfDays)); 
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

//this function update existing Training schedule  
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

    FILE *file = fopen(TRAINING_FILE, "r");
    FILE *tempFile = fopen("db-files/temp.txt", "w");   // create temporary file in write and insert updated data on it

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

    remove(TRAINING_FILE); // remove old original file
    rename("db-files/temp.txt", TRAINING_FILE); // rename updated temporary file into original file

}
}


// this function allocate training schedule to the faculty and store the into allocatedTraining.txt file
void allocateTrainingToFaculty(){
    long int batchId;
    char userName[30];
    printf("\n          *** allocate Training To Faculty ***\n");
    printf("\nEnter the BatchId To Allocate To Tranier : ");
    scanf("%ld",&batchId);
    if(isBatchIdPresent(batchId)){ // check batchId training present or not
        printf("\nEnter the faculty email to assing the batch : ");
        scanf("%s",userName);
        if(isUserNamePresent(userName)){ // check faculty registered ot not
            Training training;
            FacultyAssignments facultyAssignments;
            FILE * trianingFile = fopen(TRAINING_FILE,"r");
            FILE * allocatedTrainingFile = fopen(ALLOCATED_TRAINING_FILE,"a");
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
              printf("\n______________________________________________________________________\n");
              printf("\n\t\t*** Allocate schedule to faculty Successful ***\n\n");
              // after Successful training allocation this function display allocated schedule 
              facultyAssignmentsDisplay(facultyAssignments); 
            }

        }else{
            printf("\n\t\tFaculty not found with %s !!!",userName);
        }
    } else {
        printf("\n\t\t%ld BatchId is not found !!!",batchId);
    }
}


// this function check training exist or not based of batchId
bool isBatchIdPresent(long int batchId){
     Training training;
     FILE* file = fopen(TRAINING_FILE, "r"); 
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


// generate Report of on going training based on stream wise
void generateReport(){
    FILE *file = fopen(ALLOCATED_TRAINING_FILE,"r");
    FacultyAssignments facultyAssignments;
    printf("\n\t\t\t\t\t\t ** TRAINING  REPORT **");
    if(file==NULL){

        printf("\n\t\tNo recoed found");
    } else{
        while(
            fscanf(file,"%ld,%[^,],%[^,],%d,%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n",
                    &facultyAssignments.batchId, facultyAssignments.technology, facultyAssignments.startDate, 
                    &facultyAssignments.noOfDays,facultyAssignments.endDate, facultyAssignments.venueDetail, 
                    &facultyAssignments.noOfParticipants, facultyAssignments.month
                    ,facultyAssignments.facultyEmail,facultyAssignments.status) !=EOF)
            displayReportData(facultyAssignments);
    }
    fclose(file);
}

// this function display the data of Report
void displayReportData(FacultyAssignments facultyAssignments){
    printf("\n_______________________________________________________________________________________________________________________________\n\n");
    printf("Stream Name : %s\t\t\t\t\t\t\t",facultyAssignments.technology);
    printf("\t\t\t\tBatch ID : %ld\n\n",facultyAssignments.batchId);
    printf("Batch Start on %s   Participants : %d  Venue : %s  Faculty Email : %s  Training Status : %s\n"
    ,facultyAssignments.month,facultyAssignments.noOfParticipants,facultyAssignments.venueDetail
    ,facultyAssignments.facultyEmail,facultyAssignments.status);
}
