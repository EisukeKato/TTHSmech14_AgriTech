#include "Motor.h"
#include <Arduino.h>
//#include <Servo.h>

Drive *drive;
Motor *chainMotor;
Platform *platform;
Intake *intake;


extern HardwareSerial Serial;

int run = 150;
byte val = 0;
void movePlatform();
int microSW();
void moveIntakeArm(bool a);
void movePlatform();

const bool test = true;

int pin[3][2] = {{2,3},{5,4},{6,7}};
int pin_rotServo[2] = {10,11};
int pin_intakeServo[2] = {8,9};
int pin_switch[2] = {15,16};
int pin_Intake = 14;

const int siz = 2000;
int swRealArchive[siz]{0};
int swJudgeArchive[2]{0};
int swTime = 0;

void setup(){
    Serial.begin(115200);
    if (test) {
        for (int i = 3; i >= 1; --i) {
            Serial.println(i);
            delay(1000);
        }
    }

    pinMode(pin_Intake,INPUT_PULLUP);
    drive = new Drive(pin[0],pin[1]);
    chainMotor = new Motor(pin[2]);
    platform = new Platform(pin_rotServo, pin_switch);
    intake = new Intake(pin_intakeServo);
    intake->pull();
    platform->Down();
    platform->Move(0);
}

void loop(){
    if (!test) {

        if(Serial.available() > 0){

                    val = Serial.read();
                    Serial.print(val); //for debug
        }
        else if(val == 'f'){//前進
            drive->Move(255,245);
            Serial.println("うごけー！");
        }

        else if(val == 'b'){//後退
            drive->Move(-255,-245);
            Serial.println("うごけー！");
        }

        else if(val == 'l'){//左
            drive->Move(-255,245);
            Serial.println("うごけー！");
        }

        else if(val == 'r'){//右
            drive->Move(255,-245);
            Serial.println("うごけー！");
        }

        else if(val == 'i'){//回収
            drive->Move(150,150);
            moveIntakeArm(true);
            Serial.println("うごけー！");
        }
        else if(val == 's'){//停止
            drive->Move(0,0);
            chainMotor->Move(0);
            Serial.println("とまれー！");
        }
        else if(val == 'p'){//荷台
            drive->Move(0,0);
            chainMotor->Move(0);
            Serial.println("とまれー！");
        }
        else if(val == 'o'){
            moveIntakeArm(false);
        }

        else if(val == '0'){
            Serial.println("信号なし");
        }

    } else{
//        drive->Move(200,200);
        movePlatform();
        delay(3000);
    }
                
}

int microSW(){
    chainMotor->Move(255);
    int swNow = digitalRead(pin_Intake);
    for (int i = siz - 1; i >= 1; --i) swRealArchive[i] = swRealArchive[i-1];
    swRealArchive[0] = swNow;
    int swMax = 0; int swMin = 1;
    int swJudge = 0;
    for (int i = 0; i < sizeof(swRealArchive); ++i) {
        if (swRealArchive[i] > swMax) swMax = swRealArchive[i];
        if (swRealArchive[i] < swMin) swMin = swRealArchive[i];
        if (swMax == swMin){
            swJudgeArchive[1] = swJudgeArchive[0];
            swJudgeArchive[0] = swMax;
            break;
        }
    }
    if (swMax != swMin) {
        swJudgeArchive[0] = swJudgeArchive[1];
    }
    return swJudgeArchive[0];
}

void moveIntakeArm(bool a){//true:move false stop
    microSW();

    Serial.println(swJudgeArchive[0]);

    if (swJudgeArchive[0]) {
        swTime++;
        while (microSW());
        if(swTime == 1) {
            if (a){
                drive->Move(75,75);
            }
            delay(750);
            chainMotor->Stop();
            intake->push();
            delay(2500);
            intake->pull();
            delay(1000);
            while (microSW());
            swTime = 0;
        }
    }
}

void movePlatform(){
    platform->Move(10);
    delay(1500);
    platform->Move(0);

    drive->Move(-200,-200);
    delay(1500);
    drive->Move(0,0);
    delay(500);
    drive->Move(200,200);
    delay(2000);
    drive->Move(0,0);

    platform->Down();
    platform->Move(0);
    delay(1000);
}
