#include <dht.h>//temp
const int buzzerPin = 11;//fire
 const int flamePin = 2;//fire
 int Flame = HIGH;//fire

 int sensorValue;//mq135
 int digitalValue;

#define dht_apin A0//temp
dht DHT;//needed by DHT11 (for temp)

void setup()
{
  Serial.begin(9600);//temp
  delay(500);
  Serial.println("DHT11 HUMIDITY AND TEMPERATURE SENSOR\n\n");
  delay(100);//temp

  pinMode(buzzerPin, OUTPUT); //fire
  pinMode(flamePin, INPUT);
 Serial.begin(9600);//fire

//mq135
  Serial.begin(9600); // sets the serial port to 9600 
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  
}

void loop()
{
  DHT.read11(dht_apin);//temp
  Serial.print("current humidity=");
  Serial.print(DHT.humidity);
  Serial.print("% ");
  Serial.print("temperature=");
  Serial.print(DHT.temperature);
  Serial.print("c ");
  delay(5000);//temp

  Flame = digitalRead(flamePin);//fire
 if (Flame== LOW)
 { Serial.println("Fire is Detected");
 digitalWrite(buzzerPin, HIGH); 
 } 
else
 { 
Serial.println("No Fire is Detected");
 digitalWrite(buzzerPin, LOW);
 }//fire

 //mq135
  sensorValue = analogRead(0); // read analog input pin 0
  digitalValue = digitalRead(2);
  if (sensorValue > 400)
  {
    digitalWrite(13, HIGH);
  }
  else
    digitalWrite(13, LOW);
  Serial.println(sensorValue, DEC); // prints the value read
  Serial.println(digitalValue, DEC);
  delay(5000); // wait 100ms for next reading
}
