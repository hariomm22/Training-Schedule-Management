#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../../header/data.h"
#include "../../header/facultyService.h"
#define ALLOCATED_TRAINING_FILE "db-files/allocatedTraining.txt"
#define FACULTY_FILE "db-files/facultyInfo.txt"

// this function check userName in facultyInfo.txt file if record exist then return true else false
bool isUserNamePresent(char * userName){
     Faculty faculty;
     FILE* file = fopen(FACULTY_FILE, "r"); 
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


// this function check userName and passoword of faculty in facultyInfo.txt  file if record exist then return true else false
bool facultyLogin(char *userName , char *password){
    Faculty faculty;
     FILE* file = fopen(FACULTY_FILE, "r"); 
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


/* this function take  userName of faculty return corresponding faculty struct */
Faculty getLogInedFaculty(char *userName){
     Faculty faculty={0};
     FILE* file = fopen(FACULTY_FILE, "r"); 
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


// this fucntion return allocated training schedule list for particular faculty 
FacultyAssignmentsList* getScheduleDetails(char *userName){

     printf("\n\t\t\t** schedule details **");
     FacultyAssignments facultyAssignments;
     FacultyAssignmentsList *head=NULL;
     FacultyAssignmentsList *tail=NULL;
     FILE* file = fopen(ALLOCATED_TRAINING_FILE, "r"); 
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

// this function insert allocated training schedule into FacultyAssignmentsList
void insertFacultyAssignmentsInFacultyAssignmentsList(FacultyAssignmentsList **head , FacultyAssignmentsList **tail,FacultyAssignmentsList *newFacultyAssignments){
    if((*head)==NULL){
        (*head)=newFacultyAssignments;
        (*tail)=newFacultyAssignments;
    }else{
        (*tail)->link=newFacultyAssignments;
        (*tail)=newFacultyAssignments;
    }
}


// this function display faculty assignment 
void facultyAssignmentsDisplay(FacultyAssignments facultyAssignments){
    printf("\n______________________________________________________________________\n\n");
    printf(" Batch Id : %ld\n\n",facultyAssignments.batchId);
    printf(" Technology : %s\n\n",facultyAssignments.technology);
    printf(" Start Date to Training : %s\n\n",facultyAssignments.startDate);
    printf(" Number of Days for Training : %d\n\n",facultyAssignments.noOfDays);
    printf(" End Date to Training : %s\n\n",facultyAssignments.endDate);
    printf(" Training Venue Details : %s\n\n",facultyAssignments.venueDetail);
    printf(" Number of participants in Training : %d\n\n",facultyAssignments.noOfParticipants);
    printf(" Month which training Start : %s\n\n",facultyAssignments.startDate);
    printf(" Trainer Email address : %s\n\n",facultyAssignments.facultyEmail);
    printf(" Training Current Status : %s\n\n",facultyAssignments.status);
}


// this function update allocated training status allocated to cancel request
bool requestToCancelAllocatedSchedule(long int batchId , char *userName){

    bool flag = false;
    FacultyAssignments facultyAssignments;
    FILE* file = fopen(ALLOCATED_TRAINING_FILE, "r");
    FILE *tempFile = fopen("db-files/temp.txt", "w"); // create temporary file in write mood and insert updated data on it
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
            strcpy(facultyAssignments.status,"Cancel request");
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
    remove(ALLOCATED_TRAINING_FILE);   // remove old original file
    rename("db-files/temp.txt", ALLOCATED_TRAINING_FILE);  // rename updated temporary file into original file

    return flag;
    
}
