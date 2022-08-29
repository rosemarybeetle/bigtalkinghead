/*

  ===================  Servo script  =========================
  rosemarybeetle - basic 2 servo script to
  - use two potentiometers to control eyeball tracking in two dimensions
  - left-right and up-down
  https://makingweirdstuff.blogspot.com
  
*/


// ===============================================================================
// ============== declaring global variables and including libraries etc =========
// ===============================================================================


#include <Servo.h> // Include the Servo library 
int pot_in_LR = analogRead(0); // reads value from potentiometer on pin A0 (left - right)
int pot_in_UD = analogRead(1); // reads value from potentiometer on pin A1 (up - down)
int pot_in_recentre = analogRead(2); // reads value from button switch on pin A2 (recentre)
int eye_position_LR = 90; // initialise left-right position flag with servo - 90 represents centered
int eye_position_UD = 90; // initialise up-down position with servo - 90 represents centered
int centre = 90; // degrees for centered position (90 for a 180 degree servo)
int left_max = 70; // indicates maximum degrees of left hand rotation from centre
int right_max = 105; // indicates maximum degrees of right hand rotation from centre
int down_max = 0; // indicates maximum degrees of downwards rotation from centre
int up_max = 180; // indicates maximum degrees of upwards rotation from centre
int delay_smoothing = 10; // used to delay a signal, to check so that analogue signals don't get caught by the loop too quickly causing one to supercede another before it has happened
int threshold_L = 1000; // analogue signal over which a move is triggered left
int threshold_R = 10; // analogue signal over which a move is triggered right
int threshold_D = 800; // analogue signal over which a move is triggered down
int threshold_U = 100; // analogue signal over which a move is triggered up
int trigger_LR = 0; // initialise activity trigger_LR flag
int trigger_UD = 0; // initialise activity trigger_UD flag

int servo_pin_LR = 2; // servo control output for left-right servo
int servo_pin_UD = 3; // servo control output for up-down servoint left_flash = 8;
int flash_butt = 13; // define output for button press indicator LED
int flash_left = 11; // define output for left indicator LED
int flash_right = 10; // define output for right indicator LED
int flash_down = 9;  // define output for down indicator LED
int flash_up = 8;  // define output for up indicator LED

int degrees_per_move_LR = 10; // initialise movement increment (degrees)for left-right
int degrees_per_move_UD = 10; // initialise movement increment (degrees)for up-down

int loop_count = 0;
int loop_count_max=50;
int button_lag_check=0;
int button_lag_threshold=70; //  this stops button presses triggering in quick succession interfering with directional inputs
Servo servo_LR; // declare left right servo
Servo servo_UD; // declare up-down servo

// ===============   end global variables  =================================
// =========================================================================
void setup() {
  Serial.begin(57600);  // initiate port connection - used here for debugging
  pinMode(servo_pin_LR, OUTPUT);  // define pin modes of servo_pin_LR for left right control signal
  pinMode(servo_pin_UD, OUTPUT);  // define pin modes of servo_pin_UD for up down control signal
  pinMode(flash_butt, OUTPUT);
  pinMode(flash_left, OUTPUT);
  pinMode(flash_right, OUTPUT);
  pinMode(flash_down, OUTPUT);
  pinMode(flash_up, OUTPUT);
  servo_LR.attach(servo_pin_LR); // attaches servo_LR to control_pin_LR  
  servo_UD.attach(servo_pin_UD); // attaches servo_UD to control_pin_UD
  servo_LR.write(eye_position_LR); // centre servo_LR
  servo_UD.write(eye_position_UD); // centre servo_UD
 
 
}
// ====================== end of setup ===============================
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//  ===================== start of loop()=============================
void loop() {

  //  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  
  //  ------  manage loop timers -------------------------------------
  if (loop_count<loop_count_max) // only used for debugging (to indicate the loop duration)
  {
    loop_count++;
  } else {
   Serial.print("loop_count_max = ");
   Serial.println(loop_count_max);
     loop_count=0;
  }

  if (button_lag_check<button_lag_threshold) // increments timer to stop button presses happening repeatedly if a finger is released slowly
  {
    button_lag_check++;
  } else {
   Serial.print("button_check_threshold reached at ");
   Serial.print(button_lag_threshold);
   Serial.println(" loops");
     
  }
  //  ----------------  end loop timer check  ------------------------
  //  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  
  // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  //-----------   check all analogue inputs each loop() sweep  ---------------------
  
  pot_in_LR = analogRead(0); // check left-right pot control value via analogue 0 
  pot_in_UD = analogRead(1); // check up-down pot control value via analogue 1 
  pot_in_recentre = analogRead(2); // reads value from button switch on pin A2 (recentre)

  //  ---------------------  end check pots ---------------------------------
  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  // ---------------  check for eye position reset  -------------------------
  if (pot_in_recentre==0){ // reset eyes to centre if button is pressed
      digitalWrite(flash_butt,LOW);
      Serial.println("button pressed");
      if (button_lag_check==button_lag_threshold){ 
      digitalWrite(flash_butt,HIGH);
      servo_LR.write(90); // centre left/right (servo_LR)
      servo_UD.write(90); // centre up/down (servo_UD)
      button_lag_check=0;
      }  else {
      Serial.println("button press not effective till threshold met");
      }
  }
  // ---------------------  end recentre panic button  ------------------
  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  
  //  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  //  =====================   go_left detector  =========================
    if (trigger_LR==0){ // check if trigger is set for left-right checking
      trigger_LR=1; // if not set, then set left-right trigger to lock the function from being called again until it has finished
      digitalWrite(flash_left,LOW);
      if (pot_in_LR >threshold_L) { // catch-all left hand thumb move detected on the control pot. this shouldn't be too close to the central value or it may get trigger_LRed accidentally
        digitalWrite(flash_left,HIGH);
        Serial.print("pot_in_LR = "); // debug trace
        Serial.println(pot_in_LR);  // debug trace
        Serial.println("inside go_left DETECTOR and moving"); // debug trace to say where we are
        Serial.print("eye_position_LR=");
        Serial.println(eye_position_LR);
        if (eye_position_LR > left_max) { // don't go right if already at maximum right
            eye_position_LR -= degrees_per_move_LR; // decrement by left-right degree per move setting
            servo_LR.write(eye_position_LR);
            Serial.print("eye_position_LR=");
            Serial.println(eye_position_LR);
            } else { // Checks if calculation would exceed left limit
            eye_position_LR=left_max; // if so, restricts eye position to be left limit
            servo_LR.write(eye_position_LR); // then writes to servo 
            Serial.println("Reached maximum lefthand rotation limit (left_max)"); // debug trace
        }
       
 
      }  //  end  =========if(pot_in_LR > 800) ===
       else {  // optional else where degugging can be placed
        // e.g. - Serial.println("some message");
      }
      delay(delay_smoothing);
       trigger_LR=0; // reset trigger
    }
    //  ====================  end left detector ========================
    //  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    
    //  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //  ====================  go right detector    =====================
      if (trigger_LR==0){
      trigger_LR=1;
      digitalWrite(flash_right,LOW);
      if (pot_in_LR < threshold_R) { // catch-all left hand thumb move detected on the control pot. this shouldn't be too close to the central value or it may get trigger_LRed accidentally
        digitalWrite(flash_right,HIGH);
        Serial.print("pot_in_LR = ");
        Serial.println(pot_in_LR);
        Serial.println("inside go_right DETECTOR and moving"); //
        Serial.print("eye_position_LR=");
        Serial.println(eye_position_LR);
        if (eye_position_LR < right_max) { // don't go right if already at maximum right
            eye_position_LR += degrees_per_move_LR;
            servo_LR.write(eye_position_LR);
            } else {
            eye_position_LR=right_max;
            Serial.println("Reached maximum lefthand rotation limit (left_max)");
        }
       
 
      }  //  end  =========if(pot_in_LR > 800) ===
       else { // optional else where degugging can be placed
        // e.g. - Serial.println("some message");
      }
       delay(delay_smoothing);
       trigger_LR=0; // reset trigger
    }
    // ==========   end go right detector - if(pot_in_LR > 800 )==========
    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 
    // >>>>>>>>>>  go down detector  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    // ===================================================================
    if (trigger_UD==0){ // check if trigger is set for up-down checking
      trigger_UD=1; // if not set, then set - trigger to lock the function from being called again until it has finished
      digitalWrite(flash_down,LOW);
      if (pot_in_UD >threshold_D) { // catch-all down hand thumb move detected on the control pot. this shouldn't be too close to the central value or it may get triggered accidentally
        digitalWrite(flash_down,HIGH);
        Serial.print("pot_in_UD = "); // debug trace
        Serial.println(pot_in_UD);  // debug trace
        Serial.println("inside go_down DETECTOR and moving"); // debug trace to say where we are
        Serial.print("eye_position_UD=");
        Serial.println(eye_position_UD);
        if (eye_position_UD > down_max) { // don't go down if aUDeady at maximum down
            eye_position_UD -= degrees_per_move_UD; // increment by up-down degree per move setting
            servo_UD.write(eye_position_UD);
            Serial.print("eye_position_UD=");
            Serial.println(eye_position_UD);
            } else { // Checks if calculation would exceed down limit
            eye_position_UD=down_max; // if so, restricts eye position to be down limit
            servo_UD.write(eye_position_UD); // then writes to servo 
            Serial.println("Reached maximum downhand rotation limit (down_max)"); // debug trace
        }
       
 
      }  //  end  =========if(pot_in_UD > thtreshold_D) ===
       else {  // optional else where degugging can be placed
        // e.g. - Serial.println("some message");
      }
      delay(delay_smoothing);
       trigger_UD=0; // reset trigger
    }
    //  ====================  end down detector ========================
    //  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// >>>>>>>>>>  go up detector  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    // ===================================================================
    if (trigger_UD==0){ // check if trigger is set for up-down checking
      trigger_UD=1; // if not set, then set - trigger to lock the function from being called again until it has finished
      digitalWrite(flash_up,LOW);
      if (pot_in_UD <threshold_U) { // catch-all up hand thumb move detected on the control pot. this shouldn't be too close to the central value or it may get triggered accidentally
        digitalWrite(flash_up,HIGH);
        Serial.print("pot_in_UD = "); // debug trace
        Serial.println(pot_in_UD);  // debug trace
        Serial.println("inside go_up DETECTOR and moving up"); // debug trace to say where we are
        Serial.print("eye_position_UD=");
        Serial.println(eye_position_UD);
        if (eye_position_UD < up_max) { // don't go up if aUDeady at maximum up
            eye_position_UD += degrees_per_move_UD; // increment by up-down degree per move setting
            servo_UD.write(eye_position_UD);
            Serial.print("eye_position_UD=");
            Serial.println(eye_position_UD);
            } else { // Checks if calculation would exceed up limit
            eye_position_UD=up_max; // if so, restricts eye position to be up limit
            servo_UD.write(eye_position_UD); // then writes to servo 
            Serial.println("Reached maximum upward rotation limit (up_max)"); // debug trace
        }
       
 
      }  //  end  =========if(pot_in_UD < threshold_U) ===
       else {  // optional else where degugging can be placed
        // e.g. - Serial.println("some message");
      }
      delay(delay_smoothing);
       trigger_UD=0; // reset trigger
    }
    //  ====================  end down detector ========================
    //  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    
  
}  // ==========  end void loop () ================================
//   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
