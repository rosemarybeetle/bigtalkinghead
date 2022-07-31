#include <Stepper.h>

const int stepsPerRevolution = 64;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
void setup() {
  pinMode(13,OUTPUT);

  // set the speed 
  myStepper.setSpeed(240);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  digitalWrite(13,HIGH);
  // step one revolution  in one direction:
  Serial.print("clockwise");
  Serial.println();
  myStepper.step(stepsPerRevolution);
  //delay(2);
  digitalWrite(13,LOW);
   delay(2);

  
}
