#include <stdio.h>
#include "../header/admin.h"
#include "../header/faculty.h"
#include "../header/adminService.h"

int main() {
    int choice;
    while (1) {
        printf("\nWelcome to Training Schedule Management\n");
        printf("1. Admin\n");
        printf("2. Faculty\n");
        printf("3. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if(adminLogin()){
                adminMenu();
                }else{
                    printf("Invalid Credicationl");
                    break;
                }
                break;
            case 2:
                facultyMenu(); // faculty menu function
                break;
            case 3:
                printf("Exiting the application.\n");
                return 0;
            default:
                printf("Invalid Input. Please try again.\n");
                break;
        }
    }
}