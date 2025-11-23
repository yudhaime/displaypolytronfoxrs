#ifndef CANBUS_H
#define CANBUS_H

bool initCAN();
void updateCAN();

extern int tempCtrl;
extern int tempMotor;
extern int tempBatt;

#endif