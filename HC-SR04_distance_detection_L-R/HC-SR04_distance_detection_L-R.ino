/*
 * created by Rui Santos, https://randomnerdtutorials.com
 * 
 * Complete Guide for Ultrasonic Sensor HC-SR04
 *
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
 */
// ====================  LEFT    ================
int trigPin_L = 12;    // Trigger L
int echoPin_L = 11;    // Echo L
// ====================  END LEFT ================


// ====================  RIGHT ================
int trigPin_R = 10;    // Trigger R
int echoPin_R = 8;    // Echo R
// ====================  END RIGHT ================
long duration_L, cm_L, inches_L;
long duration_R, cm_R, inches_R;
 
/*
====================    credits    ===============
Original tutorual code to detect basic distance was copied from:
https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/

====================    notes      ===============


*/

// --------------------------

void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin_L, OUTPUT);
  pinMode(trigPin_R, OUTPUT);
  pinMode(echoPin_L, INPUT);
  pinMode(echoPin_R, INPUT);
}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  // for both sensors
  
  // ==========   PULSES   ==============
  digitalWrite(trigPin_L, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin_L, HIGH);
   digitalWrite(trigPin_L, LOW);
 

 
  // ==========   pulses   END ==============
  
  
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.

  // ==========   READ   ==========
 
  duration_L = pulseIn(echoPin_L, HIGH);
   // ==========   END READ   ==========

// ====================== LEFT ================
// Convert the time into a distance
  cm_L = (duration_L/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches_L = (duration_L/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  Serial.print("DURATION_l=");
  Serial.print(duration_L);
  Serial.println();
  Serial.print(inches_L);
  Serial.print("in_L, ");
  Serial.println();
  Serial.print(cm_L);
  Serial.print("cm (LEFT)");
  Serial.println();
  Serial.print("-------------");
  Serial.println();
 
 
  if (inches_L < 12) {
    digitalWrite(13,HIGH);
  } 

  if (inches_L > 12) {
    digitalWrite(13,LOW);
  }
 delay(150);
// ==================== END LEFT  ============
 digitalWrite(trigPin_R, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin_R, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin_R, LOW);
 // ==================   RIGHT ==============
  duration_R = pulseIn(echoPin_R, HIGH);
 // Convert the time into a distance
  cm_R = (duration_R/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches_R = (duration_R/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  Serial.print("duration_r=");
  Serial.print(duration_R);
  Serial.println();
  Serial.print(inches_R);
  Serial.print("in_R, ");
  Serial.println();
  Serial.print(cm_R);
  Serial.print("cm (RIGHT)");
  Serial.println();
  Serial.print("-------------");
  Serial.println();
  Serial.println();
  
  delay(850);
}
