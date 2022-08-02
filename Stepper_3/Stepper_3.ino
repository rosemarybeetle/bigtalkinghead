// Global variables
int timeDelay = 900;
int pot_in = analogRead(0);

void setup(){
  // declaring the four pins to be outputs
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  // setting the inital state of the electromagnets
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);
  digitalWrite(8, HIGH);
  delay(10); // a small time delay to allow the motor to move
}// end of setup

void loop(){
  pot_in = analogRead(0);
  Serial.print("pot_in = ");
  Serial.println(pot_in);
  if (pot_in <300) {
    go_left();
  } // end go_left check
  
  if (pot_in >800)
  {
    go_right();
  }// end of go_right() check
  
  
}//end of loop

void go_left() {
  digitalWrite(10, LOW);
  digitalWrite(8, HIGH); 
  delayMicroseconds(timeDelay*500);
  for(int i=0; i<202; i++){ // looping through this chunk of code for ~ a full rotation
    digitalWrite(9, LOW);
    digitalWrite(11, HIGH);
    delayMicroseconds(timeDelay);
    digitalWrite(8, LOW);
    digitalWrite(10, HIGH);
    delayMicroseconds(timeDelay);
    digitalWrite(11, LOW);
    digitalWrite(9, HIGH);
    delayMicroseconds(timeDelay);
    digitalWrite(10, LOW);
    digitalWrite(8, HIGH);
    delayMicroseconds(timeDelay);
  }
}

 void go_right() {
  // preparing the electromagnets to go the other direction
  
  digitalWrite(10, HIGH);
  digitalWrite(8, LOW);
  delayMicroseconds(timeDelay*500);
  
  
  for(int j=0; j<204; j++){ // looping through this chunk of code for ~ a full rotation in the other direction
    digitalWrite(9, LOW);
    digitalWrite(11, HIGH);
    delayMicroseconds(timeDelay);
    digitalWrite(8, HIGH);
    digitalWrite(10, LOW);
    delayMicroseconds(timeDelay);
    digitalWrite(11, LOW);
    digitalWrite(9, HIGH);
    delayMicroseconds(timeDelay);
    digitalWrite(10, HIGH);
    digitalWrite(8, LOW);
    delayMicroseconds(timeDelay);

    }
 }

 
