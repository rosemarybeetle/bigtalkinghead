/*

Info 
-----------------------------------------
-----------------------------------------
 Rosemarybeetle stepper motor drive sketch v0
 
 Hardware:
 - 28BYJ-48 stepper motor 
 - Uln2003 Motor Driver Board
 
 Sketch
 - originally forked from Arduino help page
 https://docs.arduino.cc/learn/electronics/stepper-motors
 ----------------------------------------
 ----------------------------------------
 
 */

 // include built-in Stepper driver library 
#include <Stepper.h>


// configure number of steps to match
#define STEPS 64

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 8, 9, 10, 11);

// initialise the "previous" variable that will store the previous reading from the analog input
int previous = 0;
// initialise rotation speed to RPM_speed RPM
int RPM_speed = 240;

void setup() {
  // set the speed of the motor to RPM_speed
  stepper.setSpeed(RPM_speed);
}


void loop() {
// get the sensor value
  int val = analogRead(0);
 Serial.print("analogue value = ");
  Serial.print(val);
  Serial.println();
  


  // move a number of steps equal to the change in the
  // sensor reading
  stepper.step(val - previous);

  // remember the previous value of the sensor
  previous = val;

}
