void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);
Serial.begin (9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(13,HIGH);
delay(900);
digitalWrite(13,LOW);
delay(200);
Serial.print("loop");
Serial.println();
Serial.println();
}