#include <stdio.h>
// #include <stdbool.h>
#include <string.h>
#include "../../header/adminService.h"

int adminLogin(){
    char userName[20];
    char password[20];
    printf("\nEnter username: ");
    scanf("%s",userName);
    printf("Enter Password: ");
    scanf("%s",password);
    if(strcmp(userName,"Admin")==0 && strcmp(password,"Wipro@123")==0){
        return 1;
    }else{
        return 0;
    }
}
