#include "DHT.h"

#define DHTPIN1 2     // what pin we're connected to
#define DHTPIN2 4     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define RELAY 7
#define T_TARGET2 13
#define T_TARGET1 10

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

void setup() {
  pinMode(RELAY, OUTPUT);
  Serial.begin(9600); 
  dht1.begin();
  dht2.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(30000);  // 30 secs

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();
  
  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h1) || isnan(t1)) {
    Serial.println("Failed to read from DHT1 sensor!");
    return;
  }

  // Check if any reads failed and exit early (to try again).
  if (isnan(h2) || isnan(t2)) {
    Serial.println("Failed to read from DHT2 sensor!");
    return;
  }

  float t_avg = (t1 + t2) / 2;

  if (t_avg > T_TARGET2) {
    digitalWrite(RELAY, HIGH); // HEATER OFF
  }
  else {
    if (t_avg < T_TARGET1) {
      digitalWrite(RELAY, LOW); // HEATER ON
    }
  }
  
  Serial.print("Sensor1: Humidity: "); 
  Serial.print(h1);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t1);
  Serial.println(" *C ");

  Serial.print("Sensor2: Humidity: "); 
  Serial.print(h2);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t2);
  Serial.println(" *C ");

  Serial.print("Avg. Temp.: ");
  Serial.print(t_avg);
  Serial.println(" *C ");
  Serial.println("");


}
