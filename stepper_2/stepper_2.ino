/*
 ===================  credits  =========================
   BYJ48 Stepper motor code
   original source forked from
   Mohannad Rawashdeh
   https://www.instructables.com/member/Mohannad+Rawashdeh/
   28/9/2013
   respect to Mohannad, and to Instructables
 =======================================================
  */

#define IN1  8  // define constant for input 1
#define IN2  9  // define constant for input 2
#define IN3  10 // define constant for input 3
#define IN4  11 // define constant for input 4

int Steps = 0;  // initilise variable for counting steps??
boolean Direction = true;  // gre
unsigned long last_time;  // (https://www.arduino.cc/reference/en/language/variables/data-types/unsignedlong/)
unsigned long currentMillis ; // timer variable used in loop()
int steps_left=4095; // step counter variable
long time; // time reference used in loop comparisons
void setup()
{
Serial.begin(9600);
pinMode(IN1, OUTPUT);  // define pin modes according to #define values set earlier
pinMode(IN2, OUTPUT);  // define pin modes according to #define values set earlier
pinMode(IN3, OUTPUT);  // define pin modes according to #define values set earlier
pinMode(IN4, OUTPUT);  // define pin modes according to #define values set earlier


}
void loop()
{
  while(steps_left>0){  // initialised at 4095 above, so will start
  currentMillis = micros();  // set currentMillis to the microseconds since script started running using micros()(loops at 70 minutes)
  if(currentMillis-last_time>=1000){ // Timer check logic - "last_time" is a positive "long" (assume default value = 0). 
  stepper(1); // call function stepper with parameter 1
  time=time+micros()-last_time;
  last_time=micros(); // reset "last_time" to script clock using micros()
  steps_left--;
  }
  }
   Serial.println(time); // once loop has finished, print message to port
  Serial.println("Wait...!"); // ditto
  delay(2000); // wait 2 seconds (not sure why)
  Direction=!Direction;
  // steps_left=4095;
  steps_left=4095; // reset "steps_left" to 4095
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
