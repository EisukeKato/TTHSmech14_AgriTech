#include "Motor.h"
#include <Arduino.h>
Motor* motor;
extern HardwareSerial Serial;

void setup(){
    Serial.begin(115200);
    int pin[2] = {8,9};
    motor = new Motor(pin);
    motor->Move(255);
}

void loop(){
    motor->Move(255);
    Serial.println("うごけー！");
    delay(1000);
    motor->Move(0);
    Serial.println("とまれー！");
    delay(1000);
    motor->Move(-255);
    Serial.println("もどれー！");
    delay(1000);
    motor->Stop();
    Serial.println("すとーっぷ！");
    delay(1000);
}