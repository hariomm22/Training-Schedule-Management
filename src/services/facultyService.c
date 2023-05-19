#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../../header/data.h"
#include "../../header/facultyService.h"

bool isUserNamePresent(char * userName){
     Faculty faculty;
     FILE* file = fopen("db-files/facultyInfo.txt", "r"); 
     if(file==NULL){
        return false;
     }
     while (fscanf(file,"%[^,],%[^,],%[^,],%[^\n]\n",faculty.facultyName,faculty.technologyName,faculty.userName,faculty.password) !=EOF)
     {
        if(strcmp(faculty.userName,userName)==0){
            return true;
        }
     }
     fclose(file);
     return false;
     
}