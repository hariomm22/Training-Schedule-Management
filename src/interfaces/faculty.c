#include <stdio.h>
#include <stdlib.h>
#include "../../header/admin.h"
#include "../../header/facultyService.h"
#include "../../header/data.h"
void facultyMenu(char * userName) {
    int choice;
    // Display faculty menu options and handle user input
    Faculty faculty = getLogInedFaculty(userName);
    while (1) {
        printf("\n\n*********************************************************************\n");
        printf("\t\tWelocome %s On the Faculty Menu\n",faculty.facultyName);
        printf("*********************************************************************\n\n");
        printf("1. Get schedule details\n");
        printf("2. Cancel allocated schedule\n");
        printf("3. Back to main menu\n");
        printf("Enter your choice: ");
        if(scanf("%d", &choice) !=1){
            choice=0;
        }
        fflush(stdin);
        long int batchId;
        FacultyAssignmentsList * facultyAssignmentsList; // pointer of faculty assignment list
        FacultyAssignments facultyAssignments;
        switch (choice) {
            case 1:
                // this function return faculty assignment list
                facultyAssignmentsList=getScheduleDetails(userName); 
                if (facultyAssignmentsList!=NULL){
                    // while loop for iterate facultyAssignmentsList and display faculty assignment seprately
                    while(facultyAssignmentsList!=NULL){
                    facultyAssignments=facultyAssignmentsList->data;
                    facultyAssignmentsDisplay(facultyAssignments); // this function diplay faculty assignment 
                    facultyAssignmentsList=facultyAssignmentsList->link;
                    }
                } else{
                
                    printf("\n\n\t\t you have not assigned any training yet...!\n");
                }
                getchar();
                system("clear");
                break;
            case 2:
                printf("\nEnter the Batch Id of training which you want to cancel : ");
                scanf("%ld",&batchId);
                if(requestToCancelAllocatedSchedule(batchId,faculty.userName)){
                    printf("\n\t\tRequest raised successfully..! Admin update soon");
                }else{
                    printf("\n\t\t %ld Batchid is not allocated for you..!!",batchId);
                }
                getchar();
                getchar();
                system("clear");
                break;
            case 3:
                printf("\n\t\tReturning to the main menu.\n");
                return;
            default:
                printf("\n\t\tInvalid choice. Please try again.\n");
                getchar();
                system("clear");
                break;
        }
    }
}