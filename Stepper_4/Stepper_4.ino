/*
 *
 ===================  credits  =========================
   BYJ48 Stepper motor code
   original source forked from
   Mohannad Rawashdeh
   https://www.instructables.com/member/Mohannad+Rawashdeh/
   28/9/2013
   respect to Mohannad, and to Instructables
 =======================================================
 

 * Stepper_4 attempts to trigger movement of a set duration to a fixed rotation point then change from there to another point
 */

 

// Global variables
// ============== my additions ===================================

int pot_in = analogRead(0);
int eye_position = 0; // initialise position flag
int trigger = 0; // initialise activity trigger flag
int execute_delay = 60; //  variable to control how long to wait before executing the next step in the motor
int pause = 2000; //  variable to control how long to wait between loops

//  ==============   originals ====================================
#define IN1  8  // define constant for input 1
#define IN2  9  // define constant for input 2
#define IN3  10 // define constant for input 3
#define IN4  11 // define constant for input 4
int Steps = 0;  // initilise variable for counting steps??
boolean Direction = true;  // gre
unsigned long last_time;  // (https://www.arduino.cc/reference/en/language/variables/data-types/unsignedlong/)
unsigned long currentMillis ; // timer variable used in loop()
int steps_left= 4095; // step counter variable - this represents how many steps are left to execut, NOT steps TO the left
long time; // time reference used in loop comparisons
// ===============   end originals =================================
void setup(){
  Serial.begin(9600);  // initiate port connection
  pinMode(IN1, OUTPUT);  // define pin modes according to #define values set earlier
  pinMode(IN2, OUTPUT);  // define pin modes according to #define values set earlier
  pinMode(IN3, OUTPUT);  // define pin modes according to #define values set earlier
  pinMode(IN4, OUTPUT);  // define pin modes according to #define values set earlier
}// end of setup

void loop(){
  pot_in = analogRead(0);
  Serial.print("pot_in = ");
  Serial.println(pot_in);
  if (trigger==0) {
  
  if (pot_in <300) {
   if (eye_position != -1){ // don't go left if already at maximum left
   steps_left=1024; // 1024 steps = 90 degrees
   go_left();  // launch code to go left 90 degrees or (-1024 steps from centered)
   }
  } 
  
  if (pot_in >800)
  {
    if (eye_position != 1){ // don't go left if already at maximum left
   steps_left=1024; // 1024 steps = 90 degrees
    go_right(); // launchj code to go to 90 degrees right position (+1024 steps from centered)
   }
 
  }

  if (pot_in >301) {
  recentre();
  }
  
 }

  
}//end of loop

void go_left() {
  if (eye_position==0){
    eye_position=-1;
  }
  if (eye_position==1){
    eye_position=0;
  }
  Serial.println("inside go_left()");
  // ====================
  trigger=1;
  
  while(steps_left>0){  // initialised at 1024 above, so will start
  currentMillis = micros();  // set currentMillis to the microseconds since script started running using micros()(loops at 70 minutes)
  if(currentMillis-last_time>=execute_delay){ // Timer check logic - "last_time" is a positive "long" (assume default value = 0). 
  stepper(1); // call function stepper with parameter 1
  time=time+micros()-last_time;
  last_time=micros(); // reset "last_time" to script clock using micros()
  steps_left--; // decrement "steps_left" by 1
  Serial.print("Steps_left = ");
  Serial.println(steps_left);
  }  // end while loop ================
  
  }
   Serial.println(time); // once loop has finished, print message to port
  Serial.println("Wait...!"); // ditto
  Serial.println("=============");
  delay(pause); // wait 2 seconds (not sure why)
  if (eye_position==-1) {
    Direction=!Direction;
  }
  
  // steps_left=4095;
  //steps_left=4095; // reset "steps_left" to 4095

  //  ====================================
  Serial.println("inside go_left()");
  Serial.println();//
  Serial.print("trigger = ");
  Serial.println(trigger);
  Serial.print("eye_position = ");
  Serial.println(eye_position);
  //}
  trigger=0; // reset trigger to stop signals overriding
} // end =============   void go_left()=============

 void go_right() {
  Serial.println("inside go_right()");
 if (eye_position==0){
    eye_position=1;
  }
  if (eye_position==-1){
    eye_position=0;
  }
  // ====================
  trigger=1;
  
  while(steps_left>0){  // initialised at 1024 above, so will start
  currentMillis = micros();  // set currentMillis to the microseconds since script started running using micros()(loops at 70 minutes)
  if(currentMillis-last_time>=execute_delay){ // Timer check logic - "last_time" is a positive "long" (assume default value = 0). 
  stepper(1); // call function stepper with parameter 1
  time=time+micros()-last_time;
  last_time=micros(); // reset "last_time" to script clock using micros()
  steps_left--; // decrement "steps_left" by 1
  Serial.print("Steps_left = ");
  Serial.println(steps_left);
  }  // end while loop ================
  
  }
   Serial.println(time); // once loop has finished, print message to port
  Serial.println("Wait...!"); // ditto
  Serial.println("=============");
  delay(pause); // wait 2 seconds (not sure why)
  if (eye_position==1) {
    Direction=!Direction;
  }
  
  // steps_left=4095;
  //steps_left=4095; // reset "steps_left" to 4095

  //  ====================================
  Serial.println("inside go_left()");
  Serial.println();//
  Serial.print("trigger = ");
  Serial.println(trigger);
  Serial.print("eye_position = ");
  Serial.println(eye_position);
  //}
  trigger=0; // reset trigger to stop signals overriding
    
 }

void recentre()  {
  }

 void stepper(int xw){ // step function 
  for (int x=0;x<xw;x++){
switch(Steps){
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
void SetDirection(){
if(Direction==1){ Steps++;}
if(Direction==0){ Steps--; }
if(Steps>7){Steps=0;}
if(Steps<0){Steps=7; }
}
