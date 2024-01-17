#include <Arduino.h>
#include <AccelStepper.h>
#include "OneButton.h"
#include <Ticker.h>

#define SerialMes

#define BtnPressTicks 10

#define M1CW_IN 5
#define M1CCW_IN 6
#define M2CW_IN 7
#define M2CCW_IN 8
#define M1SpUp_IN 9
#define M1SpDn_IN 10
#define M2SpUp_IN 11
#define M2SpDn_IN 12

#define M1Dir 13
#define M1Stp 2
#define M2Dir 3
#define M2Stp 4

#define M1Speed_init 4000
#define M1Acc_init 20000
#define MaxPos 1000000000
#define M2Speed_init 4000
#define M2Acc_init 20000

long M1Speed=M1Speed_init;
long M1Acc=M1Acc_init;
long M2Speed=M2Speed_init;
long M2Acc=M2Acc_init;
int Dir1=0;
int LastDir1=0;
int Dir2=0;
int LastDir2=0;

OneButton M1CW(M1CW_IN,true);
OneButton M1CCW(M1CCW_IN,true);
OneButton M2CW(M2CW_IN,true);
OneButton M2CCW(M2CCW_IN,true);
OneButton M1SpUp(M1SpUp_IN,true);
OneButton M1SpDn(M1SpDn_IN,true);
OneButton M2SpUp(M2SpUp_IN,true);
OneButton M2SpDn(M2SpDn_IN,true);

AccelStepper M1(AccelStepper::DRIVER, M1Stp, M1Dir);
AccelStepper M2(AccelStepper::DRIVER, M2Stp, M2Dir);

void M1StartCW();
void M1StartCCW();
void M1Stop();
void M2StartCW();
void M2StartCCW();
void M2Stop();
void M1SpUpStart();
void M1SpUpStop();
void M1SpDnStart();
void M1SpDnStop();
void M2SpUpStart();
void M2SpUpStop();
void M2SpDnStart();
void M2SpDnStop();

void MStart(int, int);
void MStop(int);
void MSpUpStart(int);
void MSpUpStop(int);
void MSpDnStart(int);
void MSpDnStop(int);

void M1StartCW(){
  MStart(1,1);
}

void M1StartCCW(){
  MStart(1,-1);
}

void M1Stop(){
  MStop(1);
}

void M2StartCW(){
  MStart(2,1);
}

void M2StartCCW(){
  MStart(2,-1);
}

void M2Stop(){
  MStop(2);
}

void M1SpUpStart(){
  MSpUpStart(1);
}

void M1SpUpStop(){
  MSpUpStop(1);
}

void M1SpDnStart(){
  MSpDnStart(1);
}

void M1SpDnStop(){
  MSpDnStop(1);
}

void M2SpUpStart(){
  MSpUpStart(2);
}

void M2SpUpStop(){
  MSpUpStop(2);
}

void M2SpDnStart(){
  MSpDnStart(2);
}

void M2SpDnStop(){
  MSpDnStop(2);
}

void MStart(int Mn, int dir){
  #ifdef SerialMes
    if (dir!=0){
      Serial.print("start ");
      Serial.print(Mn);
      if (dir==1) Serial.println(" CW"); else Serial.println(" CCW");
    }
  #endif
  switch (dir){
    case 0:
      if (Mn==1) M1.move(LastDir1*M1Speed*M1Speed/2/M1Acc);
      if (Mn==2) M2.move(LastDir2*M2Speed*M2Speed/2/M2Acc);
    break;

    case 1:
    case -1:
      if (Mn==1) M1.move(dir*MaxPos);
      if (Mn==2) M2.move(dir*MaxPos);
    break;
  }

  if (dir!=0) {
    if (Mn==1) LastDir1=dir;
    if (Mn==2) LastDir2=dir;
  }
}

void MStop(int Mn){
  #ifdef SerialMes
    Serial.print("stop ");
    Serial.println(Mn);
  #endif
  MStart(Mn, 0);
}

void MSpUpStart(int Mn){
  #ifdef SerialMes
    Serial.print("Speed Up ");
    Serial.println(Mn);
  #endif
}

void MSpDnStart(int Mn){
  #ifdef SerialMes
    Serial.print("Speed Down ");
    Serial.println(Mn);
  #endif
}

void MSpUpStop(int Mn){
  #ifdef SerialMes
    Serial.print("Const speed ");
    Serial.println(Mn);
  #endif
}

void MSpDnStop(int Mn){
  #ifdef SerialMes
    Serial.print("Const speed ");
    Serial.println(Mn);
  #endif
}

void setup() {
  Serial.begin(9600);
  Serial.println("Initiated");

  M1CW.setPressMs(BtnPressTicks);
  M1CW.attachLongPressStart(M1StartCW);
  M1CW.attachLongPressStop(M1Stop);

  M1CCW.setPressMs(BtnPressTicks);
  M1CCW.attachLongPressStart(M1StartCCW);
  M1CCW.attachLongPressStop(M1Stop);

  M2CW.setPressMs(BtnPressTicks);
  M2CW.attachLongPressStart(M2StartCW);
  M2CW.attachLongPressStop(M2Stop);
  
  M2CCW.setPressMs(BtnPressTicks);
  M2CCW.attachLongPressStart(M2StartCCW);
  M2CCW.attachLongPressStop(M2Stop);

  M1SpUp.setPressMs(BtnPressTicks);
  M1SpUp.attachLongPressStart(M1SpUpStart);
  M1SpUp.attachLongPressStop(M1SpUpStop);

  M1SpDn.setPressMs(BtnPressTicks);
  M1SpDn.attachLongPressStart(M1SpDnStart);
  M1SpDn.attachLongPressStop(M1SpDnStop);
  
  M2SpUp.setPressMs(BtnPressTicks);
  M2SpUp.attachLongPressStart(M2SpUpStart);
  M2SpUp.attachLongPressStop(M2SpUpStop);

  M2SpDn.setPressMs(BtnPressTicks);
  M2SpDn.attachLongPressStart(M2SpDnStart);
  M2SpDn.attachLongPressStop(M2SpDnStop);

  M1.setPinsInverted(true,true);
  M1.setMaxSpeed(M1Speed);
  M1.setAcceleration(M1Acc);
  M1.setSpeed(0);
  M1.setCurrentPosition(0);

  M2.setPinsInverted(true,true);
  M2.setMaxSpeed(M1Speed);
  M2.setAcceleration(M1Acc);
  M2.setSpeed(0);
  M2.setCurrentPosition(0);
}

void loop() {
  M1CW.tick();
  M1CCW.tick();
  M2CW.tick();
  M2CCW.tick();
  M1SpUp.tick();
  M1SpDn.tick();
  M2SpUp.tick();
  M2SpDn.tick();
  M1.run();
  M2.run();
}
