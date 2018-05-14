int val; // navngivning af LM35 outputtet
int tempPin = 1; // her fortæller vi arduinoen hvor den skal aflæse.

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
val = analogRead(tempPin); //her læser arduinoen LM35 output signalet
float mv = (val/1024.0)*5000; // oversættes til digital signal
float cel = mv/10; // oversætter milivolt til celsius grader.  

Serial.print("TEMPRATURE = "); // Serial.print er hvor det bliver printet ud så det kan ses. 
Serial.print(cel);
Serial.print("*C");
Serial.println();
delay(1000); // hvor ofte signalet bliver opdateret i millisekunder. vi har sat vores til 1 sekund. 
}
