/*

  ===================  credits  =========================
  
*/



// Global variables
// ============== my additions ===================================

int pot_in_LR = analogRead(0); // reads value from potentiometer on pin A0 (left - right)
int pot_in_UD = analogRead(1); // reads value from potentiometer on pin A1 (up - down)
int stepper_speed = 10; // controls servo speed if needed by adding pauses
int eye_position_LR = 90; // initialise left-right position flag with servo - 90 represents centered
int eye_position_UD = 90; // initialise up-down position with servo - 90 represents centered
int degrees_per_move = 10; // designates degrees of travel per move
int position_max_LR = 90; // (must be <90) maximum left or right fotation from centre(for the servo, this is one quarter = 90 degrees in either direction)
int position_max_UD = 90; // (must be <90) designates maximum left or right fotation from centre(for the servo, this is one quarter = 90 degrees in either direction)
int centre = 90; // degrees for centered position (90 for a 180 degree servo)
int left_max = centre - position_max_LR; // indicates maximum degrees of left hand rotation from centre
int right_max = centre + position_max_LR; // indicates maximum degrees of right hand rotation from centre
int down_max = centre - position_max_UD; // indicates maximum degrees of downwards rotation from centre
int left_max = centre + position_max_UD; // indicates maximum degrees of upwards rotation from centre
int trigger_LR = 0; // initialise activity trigger_LR flag
int trigger_UD = 0; // initialise activity trigger_UD flag
int execute_delay = 1; //  @@@ ??? @@@ variable to control how long to wait before executing the next step in the motor
int pause = 5; //  @@@ ??? @@@ variable to control how long to wait between loops // make this 2000 for debugging, if needed

//  ==============    ====================================
int servo_pin_LR = 2; // servo control output for left-right servo
int servo_pin_UD = 3; // servo control output for up-down servo
int Step_LR = 0;  // initilise variable for counting Step_LR
int Step_UD = 0;  // initilise variable for counting Step_LR

Servo servo_LR; // declare left right servo
Servo servo_UD; // declare up-down servo

unsigned long last_time;  // used to record last time captured to compare against current time (https://www.arduino.cc/reference/en/language/variables/data-types/unsignedlong/)
unsigned long currentMillis ; // timer variable used in loop()
int Step_remaining_LR = 0; // step counter variable = number of remaining left-right Step_LR to execute in any one action
int Step_remaining_UD = 0; // step counter variable = number of remaining up-down Step_LR to execute in any one action
long time; // time reference used in loop comparisons
// ===============   end originals =================================
void setup() {
  Serial.begin(57600);  // initiate port connection
  pinMode(servo_LR, OUTPUT);  // define pin modes according to #define values set earlier
  pinMode(servo_UD, OUTPUT);  // define pin modes according to #define values set earlier
  servo_LR.attach(servo_pin_LR); 
  servo_UD.attach(servo_pin_UD); 
 
 
}// end of setup

void loop() {
  pot_in_LR = analogRead(0);
  pot_in_UD = analogRead(1);
  move_LR_deg=(pot_in_LR*180)/1048; // 
  move_UD_deg=(pot_in_UD*180)/1048; // 

   Serial.print("move_LR_deg = "); // send left-right degree each loop (text part of message)
   Serial.println(move_LR_deg); // ditto - this is the variable
   Serial.print("move_UD_deg = "); // send up-down control potentiometer value each loop (text part of message)
   Serial.println(move_UD_deg); // ditto - this is the variable
  if (trigger_LR == 0) { // "trigger_LR" flag prevents an action being trigger_LRed if one is already in progress - only one sector move is allowed at one time

    //  ====================  go_left detector ==============
    if (pot_in_LR < 300) { // catch-all left hand thumb move detected on the control pot. this shouldn't be too close to the central value or it may get trigger_LRed accidentally
       Serial.println("inside go_left DETECTOR"); //
      if (eye_position_LR < left_max) { // chekc we are less than maximum left eye position allowed (set by left_max)
        go_left();  // launch function to go left by Step_by_sector
      }   else { 
        Serial.println("Reached maximum left rotation limit left_max");
        }
      
    }  //  end  =========if(pot_in_LR <300) ===
    //  ====================  end left ======================

    //  ====================  go right detector    =========
    if (pot_in_LR > 800) { // catch-all right hand thumb move detected on the control pot. this shouldn't be too close to the central value or it may get trigger_LRed accidentally
       Serial.println("inside go_right DETECTOR"); //
      if (eye_position_LR != HRmax) { // don't go left if already at maximum left
        Step_remaining_LR = Step_per_sector; // set Step_LR to move to the correct number Step_LR within the defined sector size
        go_right(); // launch funbction to go right by Step_by_sector
      } // end ======== eye (eye_position_LR != HRmax)
      else {
        Serial.println("Reached maximum left rotation limit HLmax");
        }
    } // end  ======== go right detector - if(pot_in_LR > 800 )===========
 }  // end ========= if(trigger_LR==0)   ===========
    // ++++++++++++++++++++++

 if (trigger_UD == 0) { // "trigger_UD" flag prevents an up-down action being triggered if one is already in progress - only one sector move is allowed at one time
    trigger_UD = 1;
    //  ====================  go_down detector ==============
    if (pot_in_UD < 300) { // catch-all downwards thumb move detected on the control pot. this shouldn't be too close to the central value or it may get trigger_LRed accidentally
       Serial.println("inside go_down DETECTOR"); //
      if (eye_position_UD != VDmax) { // don't go down if already at maximum down eye position allowed (set by VDmax)
        Step_remaining_UD = Step_per_sector; // set Step_LR to move to the correct number Step_LR within the defined sector size
        go_down();  // launch function to go left by Step_by_sector
      }   else { 
        Serial.println("Reached maximum down rotation limit VDmax");
        }
      
    }  //  end  =========if(pot_in_VD <300) ===
    //  ====================  end down detector ======================

    //  ====================  go_up detector ==============
    if (pot_in_UD > 800) { // catch-all upwards thumb move detected on the control pot. this shouldn't be too close to the central value or it may get trigger_LRed accidentally
       Serial.println("inside go_up DETECTOR"); //
      if (eye_position_UD != VUmax) { // don't go down if already at maximum down eye position allowed (set by VDmax)
        Step_remaining_UD = Step_per_sector; // set Step_LR to move to the correct number Step_LR within the defined sector size
        go_up();  // launch function to go left by Step_by_sector
      }   else { 
        Serial.println("Reached maximum down rotation limit VUmax");
        }
      
    }  //  end  =========if(pot_in_VD >800) ==
    trigger_UD = 0;
  }  // end ========= if(trigger_UD==0)   ===========
 
    //  ====================  end down ======================
    
    
 
}  // end ==========  void loop () =================

void go_left() {
  trigger_LR = 1; // disables trigger_LRing of actions until this function has fully executed
  Direction_LR = false; // set Direction_LR of travel to be left
   Serial.println("inside go_left()");
   Serial.print("eye_position_LR before execute = ");
   Serial.println(eye_position_LR);
   Serial.print("trigger_LR = ");
   Serial.println(trigger_LR);
   Serial.print("trigger_LR = ");
   Serial.println(trigger_LR);
  if (eye_position_LR > HLmax) { // check we are not at max left position allowed
    eye_position_LR--; // decrement eye_position_LR if not at max left position
  }

  // ====================


  while (Step_remaining_LR > 0) { // initialised at Step_per_sector when function was called, so this will start loop
    currentMillis = micros();  // set currentMillis to the microseconds since script started running using micros()(loops at 70 minutes)
    if (currentMillis - last_time >= execute_delay) { // Timer check logic - "last_time" is a positive "long" (assume default value = 0).
      stepper_LR(stepper_speed); // call function stepper with parameter 1
      time = time + micros() - last_time;
      last_time = micros(); // reset "last_time" to script clock using micros()
      Step_remaining_LR--; // decrement "Step_remaining_LR" by 1
       Serial.print("Step_remaining_LR = ");
       Serial.println(Step_remaining_LR);
    }  // end while loop ================

  }
   Serial.println(time); // once loop has finished, print message to port
   Serial.println("Wait...!"); // ditto
   Serial.println("=============");
  // delay(pause); // wait a bit (not sure why)






  //  ====================================

  //
  trigger_LR = 0; // reset trigger_LR to stop signals overriding
   Serial.print("eye_position_LR after execute = ");
   Serial.println(eye_position_LR);
} // end =============   void go_left()=============

void go_right() {
  trigger_LR = 1;
  Direction_LR = 1; // set Direction_LR of travel to be right
   Serial.println("inside go_right()");
   Serial.print("eye_position_LR before execute = ");
   Serial.println(eye_position_LR);
   Serial.print("trigger_LR = ");
   Serial.println(trigger_LR);
   Serial.print("trigger_LR = ");
   Serial.println(trigger_LR);
  
  if (eye_position_LR != HRmax) { // check we are not at max right position allowed
    eye_position_LR++; // increment eye_position_LR if not at max right position
  }

  // ====================

  while (Step_remaining_LR > 0) { // initialised at Step_per_sector above, so will start
    currentMillis = micros();  // set currentMillis to the microseconds since script started running using micros()(loops at 70 minutes)
    if (currentMillis - last_time >= execute_delay) { // Timer check logic - "last_time" is a positive "long" (assume default value = 0).
      stepper_LR(stepper_speed); // call function stepper with parameter 1
      time = time + micros() - last_time;
      last_time = micros(); // reset "last_time" to script clock using micros()
      Step_remaining_LR--; // decrement "Step_remaining_LR" by 1
       Serial.print("Step_remaining_LR = ");
       Serial.println(Step_remaining_LR);
    }  // end while loop ================

  }
   Serial.println(time); // once loop has finished, print message to port
   Serial.println("Wait...!"); // ditto
   Serial.println("=============");
  //delay(pause); // wait 2 seconds (not sure why)

   Serial.print("eye_position_LR after execute = ");
   Serial.println(eye_position_LR);

  //  ====================================


  trigger_LR = 0; // reset trigger_LR to stop signals overriding

}
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  go down
void go_down() {
   trigger_UD = 1;
   Serial.println("inside go down");
   Direction_UD = true; // set Direction_UD of travel to be down
   Serial.print("eye_position_UD before execute = ");
   Serial.println(eye_position_UD);
   Serial.print("trigger_UD = ");
   Serial.println(trigger_UD);
   Serial.print("Direction_UD = ");
   Serial.println(Direction_UD);
  if (eye_position_UD != VDmax) { // check we are not at max right position allowed
    eye_position_UD--; // increment eye_position_UD if not at max right position
  }

  // ====================

  while (Step_remaining_UD > 0) { // initialised at Step_per_sector above, so will start
    currentMillis = micros();  // set currentMillis to the microseconds since script started running using micros()(loops at 70 minutes)
    if (currentMillis - last_time >= execute_delay) { // Timer check logic - "last_time" is a positive "long" (assume default value = 0).
      stepper_UD(stepper_speed); // call function stepper with parameter 1
      time = time + micros() - last_time;
      last_time = micros(); // reset "last_time" to script clock using micros()
      Step_remaining_UD--; // decrement "Step_remaining_UD" by 1
        Serial.print("Step_remaining_UD = ");
        Serial.println(Step_remaining_UD);
    }  // end while loop ================

  }
   Serial.println(time); // once loop has finished, print message to port
   Serial.println("Wait...!"); // ditto
   Serial.println("=============");
  // delay(pause); // wait 2 seconds (not sure why)

   Serial.print("eye_position_UD after execute = ");
   Serial.println(eye_position_UD);

  //  ====================================


  trigger_UD = 0; // reset trigger_UD to stop signals overriding
}

// @@@@@@@@@@@@@@@@@@@@ go up @@@@@@@@@@@@@@
void go_up() {
  Serial.println("inside go up");
   trigger_UD = 1; // set up down direction up
  Direction_UD = 0; // set Direction_UD of travel to be up
   Serial.println("inside go_up()");
   Serial.print("eye_position_UD before execute = ");
   Serial.println(eye_position_UD);
   Serial.print("trigger_UD = ");
   Serial.println(trigger_UD);
   Serial.print("Direction_UD = ");
   Serial.println(Direction_UD);

  if (eye_position_UD != VUmax) { // check we are not at max right position allowed
    eye_position_UD++; // increment eye_position_UD if not at max UP position
  }

  // ====================

  while (Step_remaining_UD > 0) { // initialised at Step_per_sector above, so will start
    currentMillis = micros();  // set currentMillis to the microseconds since script started running using micros()(loops at 70 minutes)
    if (currentMillis - last_time >= execute_delay) { // Timer check logic - "last_time" is a positive "long" (assume default value = 0).
      stepper_UD(stepper_speed); // call function stepper with parameter 1
      time = time + micros() - last_time;
      last_time = micros(); // reset "last_time" to script clock using micros()
      Step_remaining_UD--; // decrement "Step_remaining_UD" by 1
        Serial.print("Step_remaining_UD = ");
        Serial.println(Step_remaining_UD);
    }  // end while loop ================

  }
   Serial.println(time); // once loop has finished, print message to port
   Serial.println("Wait...!"); // ditto
   Serial.println("=============");
  //delay(pause); // wait 2 seconds (not sure why)

   Serial.print("eye_position_UD after execute = ");
   Serial.println(eye_position_UD);

  //  ====================================


  trigger_UD = 0; // reset trigger_UD to stop signals overriding
}
// ---------------------------------

void stepper_LR(int xw) { // step function
   for (int x = 0; x < xw; x++) {
    switch (Step_LR) {
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
    SetDirection_LR();
  }
}

// ==========================================

void SetDirection_LR() {
  if (Direction_LR == 1) {
    Step_LR++;
  }
  if (Direction_LR == 0) {
    Step_LR--;
  }
  if (Step_LR > 7) {
    Step_LR = 0;
  }
  if (Step_LR < 0) {
    Step_LR = 7;
  }
}

// =================================
void stepper_UD(int xw) { // step function
  
  for (int x = 0; x < xw; x++) {
    switch (Step_UD) {
  
      case 0:
        digitalWrite(IN5, LOW);
        digitalWrite(IN6, LOW);
        digitalWrite(IN7, LOW);
        digitalWrite(IN8, HIGH);
        break;
      case 1:
        digitalWrite(IN5, LOW);
        digitalWrite(IN6, LOW);
        digitalWrite(IN7, HIGH);
        digitalWrite(IN8, HIGH);
        break;

      case 2:
        digitalWrite(IN5, LOW);
        digitalWrite(IN6, LOW);
        digitalWrite(IN7, HIGH);
        digitalWrite(IN8, LOW);
        break;
      case 3:
        digitalWrite(IN5, LOW);
        digitalWrite(IN6, HIGH);
        digitalWrite(IN7, HIGH);
        digitalWrite(IN8, LOW);
        break;
      case 4:
        digitalWrite(IN5, LOW);
        digitalWrite(IN6, HIGH);
        digitalWrite(IN7, LOW);
        digitalWrite(IN8, LOW);
        break;
      case 5:
        digitalWrite(IN5, HIGH);
        digitalWrite(IN6, HIGH);
        digitalWrite(IN7, LOW);
        digitalWrite(IN8, LOW);
        break;
      case 6:
        digitalWrite(IN5, HIGH);
        digitalWrite(IN6, LOW);
        digitalWrite(IN7, LOW);
        digitalWrite(IN8, LOW);
        break;
      case 7:
        digitalWrite(IN5, HIGH);
        digitalWrite(IN6, LOW);
        digitalWrite(IN7, LOW);
        digitalWrite(IN8, HIGH);
        break;
      default:
        digitalWrite(IN5, LOW);
        digitalWrite(IN6, LOW);
        digitalWrite(IN7, LOW);
        digitalWrite(IN8, LOW);
        break;
    }
    SetDirection_UD();
  }
}

// =================================
void SetDirection_UD() {
  
  if (Direction_UD == 1) {
    Step_UD++;
  }
  if (Direction_UD == 0) {
    Step_UD--;
  }
  if (Step_UD > 7) {
    Step_UD = 0;
  }
  if (Step_UD < 0) {
    Step_UD = 7;
  }
}
