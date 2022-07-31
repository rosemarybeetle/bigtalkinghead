// ============================
#include <Stepper.h>

// change this to the number of steps on your motor
const int STEPS = 64;

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 8, 9, 10, 11);

// the previous reading from the analog input
int previous = analogRead(0);
int val = analogRead(0);
int diff = val-previous;

void setup() {
  // set the speed of the motor to (RPM)
  stepper.setSpeed(240);
  Serial.println("===========");

}

void loop() {
  // get the sensor value
  val= analogRead(0);
  Serial.print("val = ");
  Serial.println(val);
   Serial.print("previous = ");
  Serial.println(previous);
diff = val-previous;
 Serial.print("diff = ");
  Serial.println(diff);
  // move a number of steps equal to the change in the
  // sensor reading
  delay(100);
if (diff >0) {
  stepper.step(diff);
}
if (diff <=0) {
  stepper.step(-diff);
}
  // remember the previous value of the sensor
  previous = val;
  delay(50);
}
