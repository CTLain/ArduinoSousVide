#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 8 //set DS18B20 DQ pin
#define RELAY_CONTROL_PIN 9 //set REPLY's interupt control pin
int  R_Int = RELAY_CONTROL_PIN;
#define Sous_Temp 59 //set temperature here

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {

  Serial.begin(9600);

  Serial.println("Temperature Sensor Start");

  pinMode(R_Int,OUTPUT);
  sensors.begin();
}

void loop() {

  sensors.requestTemperatures();

  Serial.println(sensors.getTempCByIndex(0));
  if (sensors.getTempCByIndex(0) < Sous_Temp)
  {
    digitalWrite(R_Int,HIGH); //turn on power, common pin to NC
  } else{
    digitalWrite(R_Int,LOW);  //turn off power, common pin to NO
  }

  delay(1000);
}
