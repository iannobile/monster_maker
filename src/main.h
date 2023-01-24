// SPDX-FileCopyrightText: 2019 Ian Nobile
//
// SPDX-License-Identifier: MIT
#ifndef _MAIN_H
#define _MAIN_H
#define VERSION 0.2
#define LOG_STATUS true
#define WARMUP 10000         // Allow the system time to settle after initializing everything.
#define PIR_PIN  D0         // PIR (motion) Sensor input pin
#define SOLENOID0_PIN D1    // Solenoid 1 input pin
#define SERVO1_PIN D2    // Solenoid 2 input pin 
#define HIT0_PIN D3         // Play Hit1 Sound output pin
#define HIT1_PIN D4         // Play Hit2 Sound output pin
#define HIT2_PIN D5         // Play Hit3 Sound output pin
#define HIT3_PIN D6         // Play Hit4 Sound output pin
#define HIT4_PIN D7         // Play Hit5 Sound output pin
#define HIT5_PIN A0         // Play Hit5 Sound output pin
#define PRESSURE_PIN A1     // Pressure sensor analog input pin

/* Function and class defintions. */
void setup();
void loop();
int blinkled(int ledColor, int pause);
int triggersolenoid(int solenoid, int direction);
int triggerservo(Servo activeServo, int degree);
int playsound(int soundPin, bool init);
#endif /* end of include guard:  */