#include <DHT.h>

#define PIN 4

int i = 0;

DHT dht( PIN, DHT11 );

void setup()
{
  Serial.begin(115200);
  Serial.println("DHT TEST PROGRAM ");
  Serial.println();
  Serial.println("Count,\tHumidity (%),\tTemperature (C)");
}

void loop()
{  
  delay(2000);

  i ++;

  dht.read();
  
  float temp     = dht.readTemperature();
  float humidity = dht.readHumidity();

  if ( isnan(temp) || isnan(humidity) ) {
    Serial.println( "Bad read!" );
    return;
  }
  
  // DISPLAY DATA
  Serial.print( i );
  Serial.print(",\t");
  Serial.print(humidity, 1);
  Serial.print("%,\t\t");
  Serial.print(temp, 1);
  Serial.print("c");
  Serial.print("\t");

  int j;
  for ( j = 0; j < (int)temp; j ++ ) {
    Serial.print('#');
  }
  Serial.println();
}

