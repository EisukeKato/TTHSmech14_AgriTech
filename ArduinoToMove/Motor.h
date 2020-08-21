//
// Created by 加藤英祐 on 2020/08/20.
//

#ifndef ARDUINOTOMOVE_MOTOR_H
#define ARDUINOTOMOVE_MOTOR_H

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

#endif //ARDUINOTOMOVE_MOTOR_H
