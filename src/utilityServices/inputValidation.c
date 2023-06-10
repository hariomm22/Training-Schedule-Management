#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../header/inputValidation.h"

bool nameCheck(char *name){
    bool flag=true;
    int len =(int)strlen(name);
    if(!isalpha(name[0])){
        return false;
    }
    for(int i=1;i<len;i++){
        if(!(isalpha(name[i]) || isspace(name[i]))){
            flag=false;
            break;
        }
    }
    return flag;
}

char * tolowerEmail(char * email){
    int len =(int)strlen(email);
    for(int i=0;i<len;i++){
        email[i]=tolower(email[i]);
    }
    return email;
}

bool emailCheck(char *email){
    bool flag=false;
    int len=strlen(email);
    if(!isalpha(email[0])){
        return flag;
    }
    char *endOfEmail;
    endOfEmail = strstr(email,".com");
    if(!(endOfEmail && strcmp(endOfEmail,".com")==0)){
        return flag;
    }
    for(int i=2;i<len-6;i++){
        if(email[i]=='@'){
            if(isalpha(email[i+1]) || isdigit(email[i+1])){
                flag=true;
                break;
            }
        }
    }
    return flag;
}