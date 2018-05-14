int GasLevel; // navngivning af MQ135 indputtet
int Temperatur; // navngivning af LM35 indputtet
//int digitalValue;
String quality="";
int buzz = 6;



void setup()
{
  Serial.begin(9600);      // sets the serial port to 960
  pinMode(buzz,OUTPUT);
}


void loop()
{
  GasLevel = analogRead(A0)/13;
  Temperatur = analogRead(A1);
  digitalWrite(buzz,LOW);

  float mv = (Temperatur/1024.0)*5000; // oversættes til digital signal
  float cel = mv/10; // oversætter milivolt til celsius grader.
  

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
  Serial.print("TEMPRATURE = "); // Serial.print er hvor det bliver printet ud så det kan ses. 
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
    

  if((cel>30)||(GasLevel>175)){
    digitalWrite(buzz,HIGH);
    }

    delay(2000);
}







