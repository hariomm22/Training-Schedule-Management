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
