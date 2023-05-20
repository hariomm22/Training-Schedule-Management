#include <stdio.h>
#include "../../header/admin.h"
#include "../../header/adminService.h"

void adminMenu() {
    int choice;
   
    while (1) {
        printf("\n\n*********************************************************************\n");
        printf("\t\tWelcome to Admin Dashboard\n");
        printf("*********************************************************************\n\n");
        printf("1. Add new Faculty\n");
        printf("2. Create new training schedule\n");
        printf("3. Update existing schedule\n");
        printf("4. Allocate schedule to faculty\n");
        printf("5. Generate training report\n");
        printf("6. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addNewFaculty();
                break;
            case 2:
                createNewTraining();
                break;
            case 3:
                updateTraining();
                break;
            case 4:
                allocateTrainingToFaculty();
                break;
            case 5:
                generateReport();
                break;
            case 6:
                printf("Returning to the main menu.\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}