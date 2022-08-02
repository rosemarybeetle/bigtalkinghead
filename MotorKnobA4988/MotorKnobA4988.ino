/*
 * MotorKnob
 *
 * A stepper motor follows the turns of a potentiometer
 * (or other sensor) on analog input 0.
 * Have a fun time experimenting with different analog sensors.
 */

#include <Arduino.h>
#include "A4988.h"//A4988 stepper motor driver library.

// change this to the number of steps on your motor
#define MOTOR_STEPS 100

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
#define DIR 8
#define STEP 9
#define ENBL 7
#define MS1 10
 #define MS2 11
 #define MS3 12
 A4988 stepper(MOTOR_STEPS, DIR, STEP, MS1, MS2, MS3);
int previous = 0;// the previous reading from the analog input
int v=0;
void setup() {
  // set the speed of the motor to 30 RPMs
  stepper.setRPM(150);//Setting the motor speed
  stepper.setMicrostep(4);
}

void loop() {
  // get the sensor value
  int val = analogRead(A2);
   v=map(val,0,1023,0,400);//0 to 1023 is the sensor range, 0 to 400 is the stepper's stepping range.

  stepper.move((v - previous)*2);

  // remember the previous value of the sensor
  previous = v;
}
