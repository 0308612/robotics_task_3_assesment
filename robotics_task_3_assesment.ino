#include <DFRobot_DS1307.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SD.h>

#define DHTTYPE DHT11;

DFRobot_DS1307 DS1307;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    Serial.begin(9600);
}

void loop() {
    Debugging();
}

void Debugging() {
  
}

long Soil(){
  
}

void DCPump() {
  
}

void Temp() {
  
}

long Light() {
  
}

void RTC() {
  
}

void SDReader() {
  
}