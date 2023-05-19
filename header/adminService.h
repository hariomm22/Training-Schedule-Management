#include <stdbool.h>
#ifndef ADMINSERVICE_H
#define ADMINSERVICE_H

int adminLogin();
void addNewFaculty();
void createNewTraining();
bool isUserNamePresent(char * );
void updateTraining();
bool isBatchIdPresent(long int);

void allocateTrainingToFaculty();
#endif