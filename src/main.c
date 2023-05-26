#include <stdio.h>
#include <stdlib.h>
#include "../header/admin.h"
#include "../header/faculty.h"
#include "../header/adminService.h"
#include "../header/facultyService.h"
#include "../header/data.h"
#define STRING_SIZE 30
int main() {
    int choice;
    //this is infinite while to display main menu (infinite untill user not exit manually by pressing appropriate key
    while (1) {
        printf("\n\n*********************************************************************\n");
        printf("\t\tWelcome to Training Schedule Management\n");
        printf("*********************************************************************\n\n");
        printf("1. Admin\n");
        printf("2. Faculty\n");
        printf("3. Quit\n");
        printf("Enter your choice: ");
        if(scanf("%d", &choice) !=1){
            choice=0;
        }
        fflush(stdin);
        char userName[STRING_SIZE];
        char password[STRING_SIZE];
        switch (choice) {
            case 1:
                if(adminLogin()){
                    system("clear");
                    adminMenu(); // adminMenu for dispolay admin menu if user successfully logined in
                    
                }else{
                    printf("\n\t\tInvalid Credicationl..!");
                    getchar();
                    getchar();
                }
                system("clear");
                break;
            case 2:
                    printf("\n\t\t*** Faculty Login ***\n");
                    printf("\n Email : ");
                    scanf(" %[^\n]s",userName);
                    printf("\n Pasword : ");
                    scanf(" %[^\n]s",password);
                if(facultyLogin(userName,password)){   // facultyLogin function check userName and password from facultyInfo.txt if credentails match then function return true else false
                    system("clear");
                    facultyMenu(userName);    // facultyMenu for dispolay particular faculty menu if faculty successfully logined in

                }else{
                    printf("\n\t\tInvalid Credicationl..!");
                }
                getchar();
                getchar();
                system("clear");
                break;
            case 3:
                printf("\n\t\t Exiting the application.\n\n");
                return 0;
            default:
                printf("\n\t\tInvalid Input. Please try again.\n");
                getchar();
                system("clear");
                break;
        }
    }
}

