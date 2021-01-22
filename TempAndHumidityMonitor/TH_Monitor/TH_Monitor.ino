/*************************/
/*Nathan Hodges          */
/*1/16/21                */
/*************************/

#include <DHT.h>

DHT dht;

void setup()
{
  pinMode(8, INPUT);
  Serial.begin(9600);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");

  dht.setup(8); //send data on pin 8
}

void loop()
{
  delay(1050); //let sensor stabilize

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  Serial.print(dht.getStatusString()); //is system functioning normally
  Serial.print("\t");
  Serial.print(humidity, 1); //single-point decimal format
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.println(dht.toFahrenheit(temperature), 1);
}
