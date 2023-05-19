#include <stdio.h>
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
        scanf("%d", &choice);
        //terst
        FacultyAssignmentsList * facultyAssignmentsList;
        FacultyAssignments facultyAssignments;
        switch (choice) {
            case 1:
                facultyAssignmentsList=getScheduleDetails(userName);
                while(facultyAssignmentsList!=NULL){
                    facultyAssignments=facultyAssignmentsList->data;
                    facultyAssignmentsDisplay(facultyAssignments);
                    facultyAssignmentsList=facultyAssignmentsList->link;
                }
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