/*

  ===================  credits  =========================
   BYJ48 Stepper motor code
   original source forked from
   Mohannad Rawashdeh
   https://www.instructables.com/member/Mohannad+Rawashdeh/
   28/9/2013
   respect to Mohannad, and to Instructables
  =======================================================


   Stepper_4 attempts to trigger movement of a set duration to a fixed rotation point then change from there to another point
*/



// Global variables
// ============== my additions ===================================

int pot_in = analogRead(0); // reads value from potentiometer on pin A0
int stepper_speed = 10;
int eye_position = 0; // initialise position flag - 0 represents centered
int sectors_max = 4; // designates maximum number of sectors of travel (NB could be dynamic)
int steps_max = 2048 / sectors_max; // designates maximum number of stepper motor steps (for the BYJ48, this is one quarter = 90 degrees)
int steps_per_sector = steps_max / sectors_max; // dymanamically calculates the steps needed to complete a sector;
int HLmax = -sectors_max; // indicates maximum sectors of left hand rotation
int HRmax = sectors_max;  // indicates maximum sectors of left hand rotation
int trigger = 0; // initialise activity trigger flag
int execute_delay = 1; //  variable to control how long to wait before executing the next step in the motor
int pause = 0; //  variable to control how long to wait between loops // make this 2000 for debugging, if needed

//  ==============   originals ====================================
#define IN1  8  // define constant for input 1
#define IN2  9  // define constant for input 2
#define IN3  10 // define constant for input 3
#define IN4  11 // define constant for input 4
int Steps = 0;  // initilise variable for counting steps??
boolean Direction = true;  // flag to treck direction of travel
unsigned long last_time;  // used to record last time captured to compare against currebnt time (https://www.arduino.cc/reference/en/language/variables/data-types/unsignedlong/)
unsigned long currentMillis ; // timer variable used in loop()
int steps_remaining = 0; // step counter variable = number of remaining steps to execute in any one action
long time; // time reference used in loop comparisons
// ===============   end originals =================================
void setup() {
  Serial.begin(57600);  // initiate port connection
  pinMode(IN1, OUTPUT);  // define pin modes according to #define values set earlier
  pinMode(IN2, OUTPUT);  // define pin modes according to #define values set earlier
  pinMode(IN3, OUTPUT);  // define pin modes according to #define values set earlier
  pinMode(IN4, OUTPUT);  // define pin modes according to #define values set earlier
}// end of setup

void loop() {
  pot_in = analogRead(0);
   Serial.print("pot_in = "); // send control potentiometer value each loop (text part of message)
   Serial.println(pot_in); // ditto - this is the variable
  if (trigger == 0) { // "trigger" flag prevents an action being triggered if one is already in progress - only one sector move is allowed at one time

    //  ====================  go_left detector ==============
    if (pot_in < 300) { // catch-all left hand thumb move detected on the control pot. this shouldn't be too close to the central value or it may get triggered accidentally
       Serial.println("inside go_left DETECTOR"); //
      if (eye_position != HLmax) { // don't go left if already at maximum left eye position allowed (set by HLmax)
        steps_remaining = steps_per_sector; // set steps to move to the correct number steps within the defined sector size
        go_left();  // launch function to go left by steps_by_sector
      }   else { 
        Serial.println("Reached maximum left rotation limit HLmax");
        }
      
    }  //  end  =========if(pot_in <300) ===
    //  ====================  end left ======================

    //  ====================  go right detector    =========
    if (pot_in > 800) { // catch-all right hand thumb move detected on the control pot. this shouldn't be too close to the central value or it may get triggered accidentally
       Serial.println("inside go_right DETECTOR"); //
      if (eye_position != HRmax) { // don't go left if already at maximum left
        steps_remaining = steps_per_sector; // set steps to move to the correct number steps within the defined sector size
        go_right(); // launch funbction to go right by steps_by_sector
      } // end ======== eye (eye_position != HRmax)
      else {
        Serial.println("Reached maximum left rotation limit HLmax");
        }
    } // end  ======== if(pot_in > 800 )===========

  }  // end ========= if(trigger==0)   ===========


}

void go_left() {
  trigger = 1; // disables triggering of actions until this function has fully executed
  Direction = false; // set direction of travel to be left
   Serial.println("inside go_left()");
   Serial.print("eye_position before execute = ");
   Serial.println(eye_position);
   Serial.print("trigger = ");
   Serial.println(trigger);
  if (eye_position > HLmax) { // check we are not at max left position allowed
    eye_position--; // decrement eye_position if not at max left position
  }

  // ====================


  while (steps_remaining > 0) { // initialised at steps_per_sector when function was called, so this will start loop
    currentMillis = micros();  // set currentMillis to the microseconds since script started running using micros()(loops at 70 minutes)
    if (currentMillis - last_time >= execute_delay) { // Timer check logic - "last_time" is a positive "long" (assume default value = 0).
      stepper(stepper_speed); // call function stepper with parameter 1
      time = time + micros() - last_time;
      last_time = micros(); // reset "last_time" to script clock using micros()
      steps_remaining--; // decrement "steps_remaining" by 1
       Serial.print("steps_remaining = ");
       Serial.println(steps_remaining);
    }  // end while loop ================

  }
   Serial.println(time); // once loop has finished, print message to port
   Serial.println("Wait...!"); // ditto
   Serial.println("=============");
  //delay(pause); // wait a bit (not sure why)






  //  ====================================

  //
  trigger = 0; // reset trigger to stop signals overriding
   Serial.print("eye_position after execute = ");
   Serial.println(eye_position);
} // end =============   void go_left()=============

void go_right() {
  trigger = 1;
  Direction = 1; // set direction of travel to be right
   Serial.println("inside go_right()");
   Serial.print("eye_position before execute = ");
   Serial.println(eye_position);
   Serial.print("trigger = ");
   Serial.println(trigger);
  if (eye_position != HRmax) { // check we are not at max right position allowed
    eye_position++; // increment eye_position if not at max right position
  }

  // ====================

  while (steps_remaining > 0) { // initialised at steps_per_sector above, so will start
    currentMillis = micros();  // set currentMillis to the microseconds since script started running using micros()(loops at 70 minutes)
    if (currentMillis - last_time >= execute_delay) { // Timer check logic - "last_time" is a positive "long" (assume default value = 0).
      stepper(stepper_speed); // call function stepper with parameter 1
      time = time + micros() - last_time;
      last_time = micros(); // reset "last_time" to script clock using micros()
      steps_remaining--; // decrement "steps_remaining" by 1
       Serial.print("steps_remaining = ");
       Serial.println(steps_remaining);
    }  // end while loop ================

  }
   Serial.println(time); // once loop has finished, print message to port
   Serial.println("Wait...!"); // ditto
   Serial.println("=============");
  //delay(pause); // wait 2 seconds (not sure why)

   Serial.print("eye_position after execute = ");
   Serial.println(eye_position);

  //  ====================================


  trigger = 0; // reset trigger to stop signals overriding

}

void stepper(int xw) { // step function
  for (int x = 0; x < xw; x++) {
    switch (Steps) {
      case 0:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        break;
      case 1:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, HIGH);
        break;

      case 2:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        break;
      case 3:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        break;
      case 4:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
      case 5:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
      case 6:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
      case 7:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        break;
      default:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
    }
    SetDirection();
  }
}
void SetDirection() {
  if (Direction == 1) {
    Steps++;
  }
  if (Direction == 0) {
    Steps--;
  }
  if (Steps > 7) {
    Steps = 0;
  }
  if (Steps < 0) {
    Steps = 7;
  }
}
