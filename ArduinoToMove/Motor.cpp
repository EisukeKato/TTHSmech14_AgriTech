//
// Created by 加藤英祐 on 2020/08/20.
//

#include "Motor.h"
#include <Arduino.h>


Motor::Motor(const int *pin) {
    for (int i = 0; i < 2; ++i) {
        motorPin[i] = *(pin + i);
    }
}

void Motor::Move(int speed) {
    if (speed>=0){
        if (speed>255) speed = 255;
        analogWrite(motorPin[0],speed);
        analogWrite(motorPin[1],0);
    } else{
        if (speed<-255) speed = -255;
        analogWrite(motorPin[0],0);
        analogWrite(motorPin[1],-speed);
    }
}

void Motor::Stop() {
    analogWrite(motorPin[0],255);
    analogWrite(motorPin[1],255);
}


Drive::Drive(int *pin0, int *pin1) {
    leftMotor = new Motor(pin0);
    rightMotor = new Motor(pin1);
}

void Drive::Move(int leftSpeed, int rightSpeed) {
    leftMotor->Move(leftSpeed);
    rightMotor->Move(rightSpeed);
    delay(1);
}

void Drive::Stop() {
    leftMotor->Stop();
    rightMotor->Stop();
    delay(1);
}
