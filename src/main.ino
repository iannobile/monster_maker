// SPDX-FileCopyrightText: 2019 Ian Nobile
//
// SPDX-License-Identifier: MIT
/*
 * Project monster_master
 * Description: A somewhat interactive monster
 * Author: Ian Nobile
 * Date: 2019-08-10
 */
#include "main.h"

int pirState = LOW;     // Set PIR state low
int hitCount = 0;       // Stores number of hits registered
int totalhitPins = 6; //number of input pins dedicated to playing sound.
bool monsterKilled = false;
int sensorForce = 0;    // Force reading of pressure sensor
int hitPins[] = { HIT0_PIN, HIT1_PIN, HIT2_PIN, HIT3_PIN, HIT4_PIN, HIT5_PIN };
Servo pullServo;  // Servo object to control the popper pull servo. A maximum of eight servo objects can be created
SerialLogHandler logHandler; // Use primary serial over USB interface for logging output


void setup() {
  // Setup function. setup() runs once, when the device is first turned on.

  Log.info("Monster Maker version %lf\nSystem version: %s", VERSION, (const char*)System.version());
  Particle.publish("Monster Maker", PRIVATE);
  Particle.publish("version", String(VERSION), PRIVATE);

  Log.info("Initializing Pins");
  pinMode(PIR_PIN, INPUT);                  // Set PIR pin to input
  pinMode(SOLENOID0_PIN, OUTPUT);           // Set Solenoid 0 pin to output
  pinMode(PRESSURE_PIN, INPUT_PULLUP);      // Set pressure sensor pin to input
  pullServo.attach(SERVO1_PIN);             // Attach servo on SERVO1_PIN pin to servo object
  pullServo.write(0);                       // test the servo by moving it to zero



// Set the audioFX pins to output mode and state to HIGH.
  playsound( 0, true);
  digitalWrite(SOLENOID0_PIN, HIGH);
  delay(WARMUP);
  digitalWrite(SOLENOID0_PIN, LOW);
  return;
}

void loop() {

  blinkled(RGB_COLOR_YELLOW, 100);
  
  sensorForce = analogRead(PRESSURE_PIN); // read the pressure pad value
  if (digitalRead(PIR_PIN) == HIGH){
    Log.info("PIR: 0");
    if (sensorForce <= 100 && monsterKilled == false ) {
      Log.info("Pressure sensor reading: %d", sensorForce);
      switch(hitCount) {
        case 0:
          Log.info("HIT 1");
          blinkled(RGB_COLOR_MAGENTA, 500);
          playsound(hitCount, false);
          hitCount = hitCount+1;
          break;
        case 1:
          Log.info("HIT 2");
          blinkled(RGB_COLOR_MAGENTA, 500);
          playsound(hitCount, false);
          hitCount = hitCount+1;
          break;
        case 2:
          Log.info("HIT 3");
          blinkled(RGB_COLOR_MAGENTA, 500);
          playsound(hitCount, false);
          hitCount = hitCount+1;
          break;
        case 3:
          Log.info("HIT 4");
          blinkled(RGB_COLOR_MAGENTA, 500);
          playsound(hitCount, false);
          hitCount = hitCount+1;
          break;
        case 4:
          monsterKilled = true;
          Log.info("DEATH");
          blinkled(RGB_COLOR_MAGENTA, 500);
          playsound(hitCount, false);
          triggerservo(pullServo, 360);
          triggersolenoid(SOLENOID0_PIN, 0);
          delay(WARMUP);
          hitCount = 0;
          break;
        default:
          Log.info("RESET");
          hitCount = 0;
      }
    }
    
    blinkled(RGB_COLOR_RED, 100);

  }
}

int blinkled(int ledColor, int pause){
  // Flash the onboard LED the passed color and wait the passed value to turn it off again.
  LEDStatus blink(ledColor, LED_PATTERN_BLINK, LED_SPEED_NORMAL, LED_PRIORITY_IMPORTANT);
  blink.setActive(true);
  delay(pause);
  blink.setActive(false);
  // LEDStatus blinkGreen(RGB_COLOR_GREEN, LED_PATTERN_BLINK, LED_SPEED_NORMAL, LED_PRIORITY_IMPORTANT);

  return 0;
}

int triggersolenoid(int solenoid, int direction){
  // Trigger the passed solenoid, reversing direction if the solenoid is a push/pull type.
  // int solenoid: Passed solenoid pin
  // int direction: direction of push/pull solenoid: 0 = pull, 1 = push
  blinkled(RGB_COLOR_WHITE, 500);
  switch(direction) {
    case 0:
      Log.info("Pulling solenoid %d", solenoid);
      digitalWrite(solenoid, HIGH);
      break;
    case 1:
      Log.info("Pushing solenoid %d", solenoid);
      digitalWrite(solenoid, LOW);
      break;
    default:
      Log.info("Pulling solenoid %d", solenoid);
      digitalWrite(solenoid, HIGH);
  }
  blinkled(RGB_COLOR_ORANGE, 500);
  // digitalWrite(solenoid, LOW);

  return 0;
}

int triggerservo(Servo activeServo, int degree){
  // Trigger the passed servomotor, setting the degrees of rotation.
  // Servo servo: Passed servo object
  // int degree: rotation of servo motor
  // Don't go past 180 degrees
  int servoPosition = analogRead(SERVO1_PIN); // variable to store the servo position
  Log.info("Servo position reading : %d", servoPosition);
  if (degree > 180) {
    degree = 180;
  }
  Log.info("Moving servo on pin %d %d degrees.", activeServo.attachedPin(), degree);
  blinkled(RGB_COLOR_WHITE, 500);
  activeServo.write(degree);    // Move the servo to the passed position
  blinkled(RGB_COLOR_GRAY, 500);
  activeServo.write(0);    // Move the servo back to zero

  return 0;
}

int playsound(int soundPin,  bool init){
  // Play a sound on the  AudioFX board by triggering a pin.
  // int soundPin: Pin to trigger
  // bool init: performs initialization of AudioFX board.
  int i = 0;
  //Initialize all the play sound pins.
  if (init == true){
    for( i = 0; i < totalhitPins; i++ ){
    Log.info("Setting hit pin i to output: %d\n", i);
    pinMode(hitPins[i], OUTPUT);
      }
  }
  // Turn all the pins off.
  for( i = 0; i < totalhitPins; i++ ){
    Log.info("Setting hit pin i: %d\n", i);
    if (digitalRead(hitPins[i]) == LOW){
        digitalWrite(hitPins[i], HIGH);
      }
   }
  if (init != true) { 
    Log.info("Playing Sound Pin # %d", soundPin);
    digitalWrite(hitPins[soundPin], LOW);
    delay(300);
    digitalWrite(hitPins[soundPin], HIGH);
  }
  return 0;
}