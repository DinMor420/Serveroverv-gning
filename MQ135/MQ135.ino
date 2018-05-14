int GasLevel;
int GasLevel2;
int digitalValue;
String quality="";

void setup()
{

  Serial.begin(9600);      // sets the serial port to 9600
  //pinMode( 1, INPUT);

}


void loop()
{
  GasLevel = analogRead(A2)/13;       // read analog input pin 0
  GasLevel2 = analogRead(A0);

  //digitalValue = digitalRead(A1); 

    // prints the value read

 if(GasLevel<175){
    quality = "GOOD! Anakin, Good";
  }
  else if (GasLevel >175 && GasLevel<225){
    quality = "Hold lige øje";
  }
  else if (GasLevel >225 && GasLevel<300){
    quality = "Dårligt";
  }
  else if (GasLevel >300){
    quality = "rigtigt dårligt";
  }

  Serial.print(quality);
  Serial.print(", ");
  Serial.println(GasLevel);
  Serial.print(", ");
  Serial.println(GasLevel2);
  //Serial.println(digitalValue);

  delay(2000);                        // wait 100ms for next reading

}
