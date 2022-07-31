//  ================================
int anal_0 = analogRead(0);
int anal_1 = analogRead(1);
 int ind_loop = 13;
 int ind_butt_press = 6;
 
//  ================================

void setup() {
 //Define inputs and outputs
 pinMode(ind_loop,OUTPUT);
 pinMode(ind_butt_press,OUTPUT);
 
 Serial.begin (9600);
}

void loop() {
  // put your main code here, to run repeatedly:

anal_0 = analogRead(0);
anal_1 = analogRead(1);
if (anal_1 >10) {
  digitalWrite(ind_butt_press,HIGH); // send button indicator pulse (LED ON)
}
Serial.print("A0 = ");
Serial.println(anal_0);
Serial.print("A1 = ");
Serial.println(anal_1);
Serial.print("loop");
Serial.println();
Serial.println();
digitalWrite(ind_loop,HIGH); // start loop indicator pulse (LED ON)
delay(9);
digitalWrite(ind_loop,LOW); // end loop indicator pulse (LED OFF)
delay(2);
if (anal_1 <10) {
  digitalWrite(ind_butt_press,LOW); // reset button indicator pulse (LED OFF
}
}
