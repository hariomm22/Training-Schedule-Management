#include <stdio.h>
// #include <stdbool.h>
#include <string.h>
#include "../../header/data.h"
#include "../../header/adminService.h"

int adminLogin(){
    Admin admin;
    printf("\nEnter username: ");
    scanf("%s",admin.userName);
    printf("Enter Password: ");
    scanf("%s",admin.password);
   
    if(strcmp(admin.userName,"Admin")==0 && strcmp(admin.password,"Wipro@123")==0){
        return 1;
    }else{
        return 0;
    }
}

void addNewFaulty(){
    FILE* file = fopen("../../db-files/facultyInfo.txt", "ab"); 
    Faculty faculty;
    printf("\nEnter Faculty Name: ");
    scanf("%s",faculty.facultyName);
    printf("Enter Technology Name: ");
    scanf("%s",faculty.technologyName);
    printf("Enter unique userName: ");
    scanf("%s",faculty.userName);
    printf("Enter Password: ");
    scanf("%s",faculty.password);
    if (file != NULL) {
        fwrite(&faculty, sizeof(faculty), 1, file);
        fclose(file);
        printf("Data inserted successfully.\n");
    } else {
        printf("Unable to open the file.\n");
    }
}