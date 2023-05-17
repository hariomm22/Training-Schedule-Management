#include <stdio.h>
#include "../../header/admin.h"

void facultyMenu() {
    int choice;
    // Display faculty menu options and handle user input
    while (1) {
        printf("\nFaculty Menu\n");
        printf("1. Get schedule details\n");
        printf("2. Cancel allocated schedule\n");
        printf("3. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        //terst

        switch (choice) {
            case 1:
                // Function to get schedule details for faculty
                break;
            case 2:
                // Function to cancel an allocated schedule
                break;
            case 3:
                printf("Returning to the main menu.\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}