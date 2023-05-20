#include <stdio.h>
#include "../header/admin.h"
#include "../header/faculty.h"
#include "../header/adminService.h"
#include "../header/facultyService.h"
#include "../header/data.h"

int main() {
    int choice;
    while (1) {
        printf("\n\n*********************************************************************\n");
        printf("\t\tWelcome to Training Schedule Management\n");
        printf("*********************************************************************\n\n");
        printf("1. Admin\n");
        printf("2. Faculty\n");
        printf("3. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        char userName[30];
        char password[30];
        switch (choice) {
            case 1:
                if(adminLogin()){
                    adminMenu();
                }else{
                    printf("\n\t\tInvalid Credicationl..!");
                }
                break;
            case 2:
                    printf("\n\t\t*** Faculty Login ***\n");
                    printf("\n Email : ");
                    scanf(" %[^\n]s",userName);
                    printf("\n Pasword : ");
                    scanf(" %[^\n]s",password);
                if(facultyLogin(userName,password)){
                    facultyMenu(userName);

                }else{
                    printf("\n\t\tInvalid Credicationl..!");
                }
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

