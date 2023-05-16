#include <stdio.h>
#include "../header/admin.h"
#include "../header/faculty.h"

int main() {
    int choice;
    while (1) {
        printf("Welcome to Training Schedule Management\n");
        printf("1. Admin\n");
        printf("2. Faculty\n");
        printf("3. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminMenu(); 
                break;
            case 2:
                facultyMenu(); // Call faculty menu function
                break;
            case 3:
                printf("Exiting the application. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}