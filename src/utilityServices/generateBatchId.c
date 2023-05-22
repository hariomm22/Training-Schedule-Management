#include <stdio.h>
#include "../../header/batchId.h"

// this function read batchid from topBatchId.txt file and return it 
int getBatchId(){
    int batchId=0;
    FILE *file = fopen("db-files/topBatchId.txt","r");
    if(file!=NULL){
        fscanf(file,"%d",&batchId);
        fclose(file);
    }
    updateBatchId(batchId);
    return batchId;
}

// this function update topBatchId.txt file (increamenting by 1 from old value)
void updateBatchId(int batchId){
    int newbatchId=(++batchId);
    FILE *file = fopen("db-files/topBatchId.txt","w");
    if(file!=NULL){
        fprintf(file,"%d",newbatchId);
        fclose(file);
    }
}