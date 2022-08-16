/*

  ===================  credits  =========================
  
*/


// ==================================================================
// ============== Global variables ===================================
// ===================================================================


#include <Servo.h> // Include the Servo library 
int pot_in_LR = analogRead(0); // reads value from potentiometer on pin A0 (left - right)
int pot_in_UD = analogRead(1); // reads value from potentiometer on pin A1 (up - down)
int servo_speed = 10; // controls servo speed if needed by adding pauses
int eye_position_LR = 90; // initialise left-right position flag with servo - 90 represents centered
int eye_position_UD = 90; // initialise up-down position with servo - 90 represents centered
int degrees_per_move = 10; // designates degrees of travel per move
int position_max_LR = 90; // (must be <90) maximum left or right fotation from centre(for the servo, this is one quarter = 90 degrees in either direction)
int position_max_UD = 90; // (must be <90) designates maximum left or right fotation from centre(for the servo, this is one quarter = 90 degrees in either direction)
int centre = 90; // degrees for centered position (90 for a 180 degree servo)
int left_max = centre - position_max_LR; // indicates maximum degrees of left hand rotation from centre
int right_max = centre + position_max_LR; // indicates maximum degrees of right hand rotation from centre
int down_max = centre - position_max_UD; // indicates maximum degrees of downwards rotation from centre
int up_max = centre + position_max_UD; // indicates maximum degrees of upwards rotation from centre

int trigger_LR = 0; // initialise activity trigger_LR flag
int trigger_UD = 0; // initialise activity trigger_UD flag
int execute_delay = 1; //  @@@ ??? @@@ variable to control how long to wait before executing the next step in the motor
int pause = 5; //  @@@ ??? @@@ variable to control how long to wait between loops // make this 2000 for debugging, if needed

int servo_pin_LR = 2; // servo control output for left-right servo
int servo_pin_UD = 3; // servo control output for up-down servo
int Step_LR = 0;  // initilise variable for counting Step_LR
int Step_UD = 0;  // initilise variable for counting Step_LR

int move_LR_deg = 10; // initialise movement increment (degrees)for left-right
int move_UD_deg = 10; // initialise movement increment (degrees)for up-down

Servo servo_LR; // declare left right servo
Servo servo_UD; // declare up-down servo

unsigned long last_time;  // used to record last time captured to compare against current time (https://www.arduino.cc/reference/en/language/variables/data-types/unsignedlong/)
unsigned long currentMillis ; // timer variable used in loop()
int Step_remaining_LR = 0; // step counter variable = number of remaining left-right Step_LR to execute in any one action
int Step_remaining_UD = 0; // step counter variable = number of remaining up-down Step_LR to execute in any one action
long time; // time reference used in loop comparisons

// ===============   end global variables  =================================
// =========================================================================
void setup() {
  Serial.begin(57600);  // initiate port connection
  pinMode(servo_pin_LR, OUTPUT);  // define pin modes of servo_pin_LR for left right control signal
  pinMode(servo_pin_UD, OUTPUT);  // define pin modes of servo_pin_UD for up down control signal
  servo_LR.attach(servo_pin_LR); // attaches servo_LR to control_pin_LR  
  servo_UD.attach(servo_pin_UD); // attaches servo_UD to control_pin_UD
  servo_LR.write(eye_position_LR); // centre servo_LR
  servo_UD.write(eye_position_UD); // centre servo_UD
 
}// end of setup

void loop() {

  //servo_LR.write(eye_position_LR);
  //servo_UD.write(eye_position_UD);  
 
 

  pot_in_LR = analogRead(0);
  pot_in_UD = analogRead(1);   
  
     //  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
     //  ====================  go_left detector =======================
    if (trigger_LR==0){
      trigger_LR=1;
      if (pot_in_LR >800) { // catch-all left hand thumb move detected on the control pot. this shouldn't be too close to the central value or it may get trigger_LRed accidentally
        Serial.print("pot_in_LR = ");
        Serial.println(pot_in_LR);
        Serial.println("inside go_left DETECTOR and moving"); //
        trace_move_degrees();
        Serial.print("eye_position_LR=");
        Serial.println(eye_position_LR);
        
        Serial.print("eye_position_LR=");
        Serial.println(eye_position_LR);
        if (eye_position_LR > left_max) { // don't go right if already at maximum right
                        eye_position_LR -= move_LR_deg;
            servo_LR.write(eye_position_LR);
            } else {
            eye_position_LR=left_max;
            Serial.println("Reached maximum lefthand rotation limit (left_max)");
        }
       
 
      }  //  end  =========if(pot_in_LR > 800) ===
       else {  
           
      //Serial.println("trigger_LR =1");
      }
      delay(20);
       trigger_LR=0; // reset trigger
    }
    //  ====================  end left detector ========================
    //  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    
    //  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //  ====================  go right detector    =====================
      if (trigger_LR==0){
      trigger_LR=1;
      if (pot_in_LR < 300) { // catch-all left hand thumb move detected on the control pot. this shouldn't be too close to the central value or it may get trigger_LRed accidentally
         Serial.print("pot_in_LR = ");
         Serial.println(pot_in_LR);
        Serial.println("inside go_right DETECTOR and moving"); //
        trace_move_degrees();
        Serial.print("eye_position_LR=");
        Serial.println(eye_position_LR);
        
        
        if (eye_position_LR < right_max) { // don't go right if already at maximum right
                        eye_position_LR += move_LR_deg;
            servo_LR.write(eye_position_LR);
            } else {
            eye_position_LR=right_max;
            Serial.println("Reached maximum lefthand rotation limit (left_max)");
        }
       
 
      }  //  end  =========if(pot_in_LR > 800) ===
       else {  
           
      //Serial.println("trigger_LR =1");
      }
       delay(20);
       trigger_LR=0; // reset trigger
    }
    
    
    // end  ======== go right detector - if(pot_in_LR > 800 )==========
    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 
     
    //  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //  ====================  start go_down detector =============
    if (pot_in_UD < 300) { // catch-all downwards thumb move detected on the control pot. this shouldn't be too close to the central value or it may get trigger_LRed accidentally
       Serial.println("inside go_down DETECTOR"); //
      if (eye_position_UD > down_max) { // don't go down if already at maximum down eye position allowed (set by VDmax)
         go_down();  // launch function to go left by Step_by_sector
      }   else { 
        Serial.println("Reached maximum down rotation limit(down_mx)");
        }
          }  //  ============  end down detector=============== =========
    //  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    
    //  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //  ====================  go_up detector ======================
    if (pot_in_UD > 800) { // catch-all upwards thumb move detected on the control pot. this shouldn't be too close to the central value or it may get trigger_LRed accidentally
       Serial.println("inside go_up DETECTOR"); //
      if (eye_position_UD < up_max) { // don't go down if already at maximum down eye position allowed (set by VDmax)
          go_up();  // launch function to go left by Step_by_sector
      }   else { 
        Serial.println("Reached maximum down rotation limit VUmax");
        }
      
    }  //  ========= end down detector - if(pot_in_VD >800) ==
    //     <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    
}  // ==========  end void loop () ================================
//   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//  ==================== start go_left() ==========================
void go_left() {
 
}  // ==================== end go_left() ============================
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ======================= start go_right() ==========================
void go_right(){
    trace_move_degrees();
    Serial.print("eye_position_LR=");
    Serial.println(eye_position_LR);
    eye_position_LR+=move_LR_deg;
     if (eye_position_LR < right_max) { // don't go right if already at maximum right
      servo_LR.write(eye_position_LR);
      } // end ======== eye (eye_position_LR != HRmax)
      else {
        eye_position_LR=right_max;
        Serial.println("Reached maximum right rotation limit (right_max)");
        }
}  // ==================== end go_right() ============================
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ======================= start go_down() ==========================
void go_down(){
    trace_move_degrees();
}  // ==================== end go_down()() ============================
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// =======================start go_up() ==========================
void go_up(){
    trace_move_degrees();

}  // ==================== end go_up() ============================
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//  ====================== start trace_move_degrees() ==========================
void trace_move_degrees() {

   Serial.print("move_LR_deg = "); // send left-right degree each loop (text part of message)
   Serial.println(move_LR_deg); // ditto - this is the variable
   Serial.print("move_UD_deg = "); // send up-down control potentiometer value each loop (text part of message)
   Serial.println(move_UD_deg); // ditto - this is the variable

}
  
