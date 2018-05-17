int GasLevel; // navngivning af MQ135 indputtet
int Temperatur; // navngivning af LM35 indputtet
int Strom = A2;
//int digitalValue;
String quality="";
int buzz = 13;
#include <LiquidCrystal.h>
int status=1;
int lys = 10;

float nVPP;   // Voltage measured across resistor
float nCurrThruResistorPP; // Peak Current Measured Through Resistor
float nCurrThruResistorRMS; // RMS current through Resistor
float nCurrentThruWire;     // Actual RMS current in Wire

float getVPP(){
  float result;
  int readValue;             // Læser sensorens output
  int maxValue = 0;          // Gemmer valuen
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //prøve for 1 sekund
   {
       readValue = analogRead(Strom);
       // ser om den nye value er større end sidste vallue
       if (readValue > maxValue) 
       {
           //hvis den er højere, bliver den til den nye maxValue
           maxValue = readValue;
       }
   }
   // converter til digital signal til volt
   result = (maxValue * 5.0)/1024.0;
  
   return result;
 }
int tid = millis()-start_time;

if((tid) < 1500) 
   {
       pinMode(lys,OUTPUT);
       /*if ((millis()-start_time) > 1500) 
       {
           pinMode(lys,0);
       }*/
   }


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup()
{
  Serial.begin(9600);      // sets the serial port to 960
  pinMode(buzz,OUTPUT);
  lcd.begin(16, 2);
  //lcd.print("hello, world!");
  //lcd.setCursor(0,0);
  //lcd.print("hej");
}


void loop()
{
  GasLevel = analogRead(A0)/13;
  Temperatur = analogRead(A1);
  //Strom = analogRead(A2);
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

nVPP = getVPP();
   
   /*
   Use Ohms law to calculate current across resistor
   and express in mA 
   */
   
   nCurrThruResistorPP = (nVPP/200.0) * 1000.0;
   
   /* 
   Use Formula for SINE wave to convert
   to RMS 
   */
   
   nCurrThruResistorRMS = nCurrThruResistorPP * 0.707;
   
   /* 
   Current Transformer Ratio is 1000:1...
   
   Therefore current through 200 ohm resistor
   is multiplied by 1000 to get input current
   */
   
   nCurrentThruWire = nCurrThruResistorRMS * 1000;

  Serial.print(quality);
  Serial.print(", ");
  Serial.println(GasLevel);
  
  Serial.print("TEMPRATURE = "); // Serial.print er hvor det bliver printet ud så det kan ses. 
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  
  Serial.print("Volts Peak : ");
  Serial.print(nVPP,3);
  Serial.println(" V");
   
  Serial.print("Strøm gennem resistor (Peak) = ");
  Serial.print(nCurrThruResistorPP,3);
  Serial.println(" mA Peak til Peak");
   
  Serial.print("Strøm gennem resistor (RMS) = ");
  Serial.print(nCurrThruResistorRMS,3);
  Serial.println(" mA RMS");
   
  Serial.print("Strøm gennem resistor = ");
  Serial.print(nCurrentThruWire,3);
  Serial.println(" mA RMS");
   
  Serial.println();

  if((cel>50)||(GasLevel>175)||(nVPP>2.000)||(nCurrThruResistorPP>5.000)){
    digitalWrite(buzz,HIGH);
    Serial.println("noget er sket");
    }

  if(cel>35){
    Serial.println("hov");
    if(status!=2){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Temperaturen er");
      lcd.setCursor(0,1);
      lcd.print("for hoj");
      status=2;
    }
   }
   else if(GasLevel>175){
    Serial.println("gert");
    if(status!=3){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Gas i luften");
      lcd.setCursor(0,1);
      lcd.print("");
      status=3;
    }
   }
   else if(nVPP>2.000){
    Serial.println("gert");
    if(status!=4){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Kortslutning:");
      lcd.setCursor(0,1);
      lcd.print("Strom");
      status=4;
    }
   }
   else if((nCurrThruResistorPP>5.000)){
    Serial.println("gert");
    if(status!=5){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Kortslutning:");
      lcd.setCursor(0,1);
      lcd.print("Strom Peak");
      status=5;
    }
   }
    else{
      if (status!=0){
        lcd.clear();
        lcd.print("Ok");
        status=0;
      }
    }
    delay(1000);
}







