//  ======  GLOBALS  ===========
//  ============================
int anal_0 = analogRead(0);
int anal_1 = analogRead(1);
 int ind_loop = 13; // LED output to see loop is looping
 int ind_butt_press = 6; // LED to show button has been pressed

#include <Stepper.h>

// change this to the number of steps on your motor
const int STEPS = 64;

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 8, 9, 10, 11);

// the previous reading from the analog input
int previous = anal_0;
int val = anal_0;
int diff = val-previous;


//-----------------------------------------------------------------

//  ========  setup() initialisation ===========
void setup() {
 //Define inputs and outputs
 pinMode(ind_loop,OUTPUT);
 pinMode(ind_butt_press,OUTPUT);
 stepper.setSpeed(240);  // set the speed of the motor to (RPM)
 Serial.begin (9600);
}
//---------------------------------------------------------------------

//  ==============main loop ======================
void loop() {
  // put your main code here, to run repeatedly:

anal_0 = analogRead(0);
anal_1 = analogRead(1);
if (anal_1 >10) {
  digitalWrite(ind_butt_press,HIGH); // send button indicator pulse (LED ON)
}
Serial.print("analogue_0= ");
Serial.println(anal_0);
Serial.print("analogue_1 = ");
Serial.println(anal_1);
Serial.print("loop");
Serial.println();
Serial.println();
digitalWrite(ind_loop,HIGH); // start loop indicator pulse (LED ON)
delay(9);
digitalWrite(ind_loop,LOW); // end loop indicator pulse (LED OFF)
delay(2);
if (anal_1 <10) {
  digitalWrite(ind_butt_press,LOW); // reset button indicator pulse (LED OFF
}
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
  
if (diff >0) {
  stepper.step(diff);
}
if (diff <=0) {
  stepper.step(-diff);
}
  // remember the previous value of the sensor
  previous = val;
}
