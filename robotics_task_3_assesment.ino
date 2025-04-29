#include <DFRobot_DS1307.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SD.h>

//#define DHTTYPE DHT11;

DFRobot_DS1307 DS1307;

//DHT dht(DHTPIN, DHTTYPE);

const int soilPin = A0;

int debug = 1;

void setup() {
    pinMode(soilPin, INPUT);

    Serial.begin(115200);
    Serial.begin(9600);
}

void loop() {
  long soilM = Soil();

  long mostureValue = map(soilM, 0 ,1023, 0, 100);

  if (debug){
    Serial.print(mostureValue);
    Serial.println("% moisture");

    delay(200);
  }
}


long Soil(){
  long value = analogRead(soilPin);
  return value;
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