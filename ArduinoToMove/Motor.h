#ifndef ARDUINOTOMOVE_MOTOR_H
#define ARDUINOTOMOVE_MOTOR_H

#include <Servo.h>

class Motor{
private:
    int motorPin[2]{};

public:
    Motor(const int*);
    void Move(int);
    void Stop();

};

class Drive{
private:
    Motor* leftMotor;
    Motor* rightMotor;

public:
    Drive(int*,int*);
    void Move(int,int);
    void Stop();
};

class Platform{
private:
    int servoPin[2]{};
    int switchPin[2]{};
    Servo* leftServo;
    Servo* rightServo;

public:
    Platform(const int*,const int*);
    void Move(int);
    void Stop();
    void Down();
    void Elevate();
};

class Intake{
private:
    int pin[2]{};
    const int rangeMax = 156;
    const int rangeMin = 24;
    Servo* leftServo;
    Servo* rightServo;

public:
    Intake(const int* pin);
    void push();
    void pull();
};

#endif //ARDUINOTOMOVE_MOTOR_H
