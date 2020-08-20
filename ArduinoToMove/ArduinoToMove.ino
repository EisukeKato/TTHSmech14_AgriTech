#include "Motor.h"
#include <Arduino.h>
Drive* drive;

void setup(){
    int pin[2][2] = {{1,2},{3,4}};
    drive = new Drive(pin[0],pin[1]);
}

void loop(){
    drive->Move(0,0);
    delay(1000);
}