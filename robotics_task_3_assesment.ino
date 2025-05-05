
#include <DFRobot_DS1307.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SD.h>

//#define DHTTYPE DHT11;

DFRobot_DS1307 DS1307;

//DHT dht(DHTPIN, DHTTYPE);

const int soilPin = A0;
const int photoPin = A1;
const int pumpPin = 3;

int debug = 1;

void setup() {
    pinMode(soilPin, INPUT);
    pinMode(photoPin, INPUT);
    pinMode(pumpPin, OUTPUT);

    Serial.begin(115200);
    Serial.begin(9600);
}

void loop() {
  long soilM = Soil();
  DCPump();
  //float photoData = Light();

  //float lightLevel = photoData * 5 / 1023 * 1000;
  long mostureValue = map(soilM, 0 ,1023, 0, 100);

  if (debug){
    Serial.print(mostureValue);
    Serial.println("% moisture");
   // Serial.print(lightLevel);
    //Serial.println("mV");

    delay(200);
  }
}


long Soil(){
  long value = analogRead(soilPin);
  return value;
}

void DCPump() {
  digitalWrite(pumpPin, LOW);
}

void Temp() {
  
}

float Light() {
  float Light = analogRead(photoPin);
  return Light;
}

void RTC() {
  
}

void SDReader() {
  
}
