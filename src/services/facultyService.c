#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../../header/data.h"
#include "../../header/facultyService.h"

bool isUserNamePresent(char * userName){
     Faculty faculty;
     FILE* file = fopen("db-files/facultyInfo.txt", "r"); 
     if(file==NULL){
        return false;
     }
     while (fscanf(file,"%[^,],%[^,],%[^,],%[^\n]\n",faculty.facultyName,
     faculty.technologyName,faculty.userName,faculty.password) !=EOF)
     {
        if(strcmp(faculty.userName,userName)==0){
            return true;
        }
     }
     fclose(file);
     return false;
     
}

bool facultyLogin(char *userName , char *password){
    Faculty faculty;
     FILE* file = fopen("db-files/facultyInfo.txt", "r"); 
     if(file==NULL){
        return false;
     }
     while (fscanf(file,"%[^,],%[^,],%[^,],%[^\n]\n",faculty.facultyName,
     faculty.technologyName,faculty.userName,faculty.password) !=EOF)
     {
        if(strcmp(faculty.userName,userName)==0 && strcmp(faculty.password,password)==0){
            return true;
        }
     }
     fclose(file);
     return false;
}

Faculty getLogInedFaculty(char *userName){
     Faculty faculty={0};
     FILE* file = fopen("db-files/facultyInfo.txt", "r"); 
     if(file==NULL){
        return faculty;
     }
     while (fscanf(file,"%[^,],%[^,],%[^,],%[^\n]\n",faculty.facultyName,
     faculty.technologyName,faculty.userName,faculty.password) !=EOF)
     {
        if(strcmp(faculty.userName,userName)==0){
            return faculty;
        }
     }
     fclose(file);
     return faculty;    
}

FacultyAssignmentsList* getScheduleDetails(char *userName){
     FacultyAssignments facultyAssignments;
     FacultyAssignmentsList *head=NULL;
     FacultyAssignmentsList *tail=NULL;
     FILE* file = fopen("db-files/allocatedTraining.txt", "r"); 
     if(file==NULL){
        return head;
     }
     while (fscanf(file,"%ld,%[^,],%[^,],%d,%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n",
                    &facultyAssignments.batchId, facultyAssignments.technology, facultyAssignments.startDate, 
                    &facultyAssignments.noOfDays,facultyAssignments.endDate, facultyAssignments.venueDetail, 
                    &facultyAssignments.noOfParticipants, facultyAssignments.month
                    ,facultyAssignments.facultyEmail,facultyAssignments.status) !=EOF)
     {
        if(strcmp(facultyAssignments.facultyEmail,userName)==0){
            // return faculty;
            FacultyAssignmentsList *newFacultyAssignments = (FacultyAssignmentsList *) malloc(sizeof(FacultyAssignmentsList));
            newFacultyAssignments->data=facultyAssignments;
            newFacultyAssignments->link=NULL;
            insertFacultyAssignmentsInFacultyAssignmentsList(&head,&tail,newFacultyAssignments);
        }
     }
     fclose(file);
     return head;    
}

void insertFacultyAssignmentsInFacultyAssignmentsList(FacultyAssignmentsList **head , FacultyAssignmentsList **tail,FacultyAssignmentsList *newFacultyAssignments){
    if((*head)==NULL){
        (*head)=newFacultyAssignments;
        (*tail)=newFacultyAssignments;
    }else{
        (*tail)->link=newFacultyAssignments;
        (*tail)=newFacultyAssignments;
    }
}

void facultyAssignmentsDisplay(FacultyAssignments facultyAssignments){
    printf("\n_____________________________________________\n");
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
    printf("\n_____________________________________________\n");
}


bool requestToCancelAllocatedSchedule(long int batchId , char *userName){

    bool flag = false;
    FacultyAssignments facultyAssignments;
    FILE* file = fopen("db-files/allocatedTraining.txt", "r");
    FILE *tempFile = fopen("db-files/temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        return flag;
    }
     while (fscanf(file,"%ld,%[^,],%[^,],%d,%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n",
                    &facultyAssignments.batchId, facultyAssignments.technology, facultyAssignments.startDate, 
                    &facultyAssignments.noOfDays,facultyAssignments.endDate, facultyAssignments.venueDetail, 
                    &facultyAssignments.noOfParticipants, facultyAssignments.month
                    ,facultyAssignments.facultyEmail,facultyAssignments.status) !=EOF)
     { 
        if( facultyAssignments.batchId == batchId && strcmp(facultyAssignments.facultyEmail,userName)==0){
            flag=true;
            strcpy(facultyAssignments.status,"Cancel request pending");
            fprintf(tempFile,"%ld,%s,%s,%d,%s,%s,%d,%s,%s,%s\n",
                    facultyAssignments.batchId, facultyAssignments.technology, facultyAssignments.startDate, 
                    facultyAssignments.noOfDays,facultyAssignments.endDate, facultyAssignments.venueDetail, 
                    facultyAssignments.noOfParticipants, facultyAssignments.month
                    ,facultyAssignments.facultyEmail,facultyAssignments.status);
        } else{
             fprintf(tempFile,"%ld,%s,%s,%d,%s,%s,%d,%s,%s,%s\n",
                    facultyAssignments.batchId, facultyAssignments.technology, facultyAssignments.startDate, 
                    facultyAssignments.noOfDays,facultyAssignments.endDate, facultyAssignments.venueDetail, 
                    facultyAssignments.noOfParticipants, facultyAssignments.month
                    ,facultyAssignments.facultyEmail,facultyAssignments.status);
        }
     }
    fclose(file);
    fclose(tempFile);
    remove("db-files/allocatedTraining.txt");
    rename("db-files/temp.txt", "db-files/allocatedTraining.txt");

    return flag;
    
}
