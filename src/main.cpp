#include <Arduino.h>
#include <AccelStepper.h>
#include "OneButton.h"
#include <Ticker.h>

#define BtnPressTicks 10

#define M1CW_IN 6
#define M1CCW_IN 7
#define M2CW_IN 8
#define M2CCW_IN 9
#define M1SpUp_IN 10
#define M1SpDn_IN 11
#define M2SpUp_IN 12
#define M2SpDn_IN 13

OneButton M1CW(M1CW_IN,true);
OneButton M1CCW(M1CCW_IN,true);
OneButton M2CW(M2CW_IN,true);
OneButton M2CCW(M2CCW_IN,true);
OneButton M1SpUp(M1SpUp_IN,true);
OneButton M1SpDn(M1SpDn_IN,true);
OneButton M2SpUp(M2SpUp_IN,true);
OneButton M2SpDn(M2SpDn_IN,true);

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

void MStart(int, bool);
void MStop(int);
void MSpUpStart(int);
void MSpUpStop(int);
void MSpDnStart(int);
void MSpDnStop(int);

void M1StartCW(){
  MStart(1,true);
}

void M1StartCCW(){
  MStart(1,false);
}

void M1Stop(){
  MStop(1);
}

void M2StartCW(){
  MStart(2,true);
}

void M2StartCCW(){
  MStart(2,false);
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

void MStart(int Mn, bool cw){
  Serial.print("start ");
  Serial.print(Mn);
  if (cw) Serial.println(" CW"); else Serial.println(" CCW");
}

void MStop(int Mn){
  Serial.print("stop ");
  Serial.println(Mn);
}

void MSpUpStart(int Mn){
  Serial.print("Speed Up ");
  Serial.println(Mn);
}

void MSpDnStart(int Mn){
  Serial.print("Speed Down ");
  Serial.println(Mn);
}

void MSpUpStop(int Mn){
  Serial.print("Const speed ");
  Serial.println(Mn);
}

void MSpDnStop(int Mn){
  Serial.print("Const speed ");
  Serial.println(Mn);
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
}
