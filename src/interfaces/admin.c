#include <stdio.h>
#include <stdlib.h>
#include "../../header/admin.h"
#include "../../header/adminService.h"

void adminMenu() {
    int choice;
   // Display faculty menu options and handle user input
    while (1) {
        printf("\n\n*********************************************************************\n");
        printf("\t\tWelcome to Admin Dashboard\n");
        printf("*********************************************************************\n\n");
        printf("1. Add new Faculty\n");
        printf("2. Create new training schedule\n");
        printf("3. Update existing schedule\n");
        printf("4. Allocate schedule to faculty\n");
        printf("5. Generate training report\n");
        printf("6. Approve cancel schedule request\n");
        printf("7. Back to main menu\n");
        printf("Enter your choice: ");
               if(scanf("%d", &choice) !=1){
            choice=0;
        }
        fflush(stdin);

        switch (choice) {
            case 1:
                system("clear");
                addNewFaculty();  // new add faculty 
                getchar();
                getchar();
                system("clear");
                break;
            case 2:
                system("clear");
                createNewTraining(); // create new training schedule
                getchar();
                getchar();
                system("clear");
                break;
            case 3:
                system("clear");
                updateTraining();   //update existing training schedule 
                getchar();
                getchar();
                system("clear");
                break;
            case 4:
                system("clear");
                allocateTrainingToFaculty(); // allocated trainer to the training 
                getchar();
                getchar();
                system("clear");
                break;
            case 5:
                system("clear");
                generateReport();  // generate report of trainnig going on with batch wise
                getchar();
                system("clear");
                break;
            case 6:
                system("clear");
                printf("\n\t\t***  Approve cancel schedule request ***\n");
                if(getCancelRequestSchedule()){
                    if(approveCancelRequest()){
                        printf("\n\t\t Request Approved..!");
                    }else{
                        printf("\n\t\tEntered Valid batch Id..!");
                    }
                    getchar();
                }else{
                    printf("\n\tNo Cancel Schdule Request Available..!");
                }
                getchar();
                system("clear");
                break;
            case 7:
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