//
// Created by 加藤英祐 on 2020/08/20.
//

#include "Motor.h"
#include <Arduino.h>


Motor::Motor(const int *pin) {
    for (int i = 0; i < 2; ++i) {
        motorPin[i] = *(pin + i);
    }
    Move(0);
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

Platform::Platform(const int* servo,const int* _switch) {
    for (int i = 0; i < 2; ++i) {
        servoPin[i] = *(servo + i);
        switchPin[i] = *(_switch + i);
    }

    leftServo = new Servo;
    rightServo = new Servo;
    leftServo->attach(servoPin[0]);
    rightServo->attach(servoPin[1]);
    pinMode(switchPin[0],INPUT_PULLUP);
    pinMode(switchPin[1],INPUT_PULLUP);
}

void Platform::Move(int power) {
    int middle = 95;
    int left = middle + power;
    int right = middle - power;
    leftServo->write(left);
    rightServo->write(right);
//    /*Serial.print("Move "); */Serial.println((String)left + "," + (String)right);
}

void Platform::Stop() {
    Move(0);
}

void Platform::Down() {
    while (switchPin[0]||switchPin[1]) Move(-3);
    Move(1); delay(500);
    Move(0);
}

void Platform::Elevate() {
    Down();
    Move(5);delay(1000);
    Move(0);
}

//156,24
Intake::Intake(const int *_pin) {
    for (int i = 0; i < 2; ++i) {
        pin[i] = *(_pin + i);
    }
    leftServo = new Servo;
    rightServo = new Servo;
    leftServo->attach(pin[0]);
    rightServo->attach(pin[1]);
    leftServo->write(rangeMin);
    rightServo->write(rangeMax);
}

void Intake::push() {
    leftServo->write(rangeMin);
//    delay(500);
    rightServo->write(rangeMax);
}

void Intake::pull() {
    leftServo->write(rangeMax);
    rightServo->write(rangeMin);
}
