//  ================================
 int analogue_0 = analogRead(0);
 int analogue_1 = analogRead(1);
//  ================================

void setup() {
 //Define inputs and outputs
 pinMode(13,OUTPUT);
 pinMode(7,OUTPUT);
 
 Serial.begin (9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(13,HIGH);
delay(900);
digitalWrite(13,LOW);
delay(200);
int analogue_0 = analogRead(0);
 int analogue_1 = analogRead(1);
Serial.print("analogue_0 = ");
Serial.println(analogue_0);
Serial.print("analogue_1 = ");
Serial.println(analogue_1);
Serial.print("loop");
Serial.println();
Serial.println();
}
