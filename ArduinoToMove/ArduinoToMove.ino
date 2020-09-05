#include "Motor.h"
#include <Arduino.h>

Drive *drive;
Motor *chainMotor;

extern HardwareSerial Serial;

int run = 150;

void setup(){
    Serial.begin(115200);
    int pin[3][2] = {{2,3},{5,4},{6,7}};
    drive = new Drive(pin[0],pin[1]);
    chainMotor = new Motor(pin[2]);
}

void loop(){
    drive->Move(255,255);
    delay(1500);
    drive->Move(255,-255);
    delay(3000);


}