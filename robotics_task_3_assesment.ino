#include <DFRobot_DS1307.h>
#include <DHT.h>
#include <SD.h>


File myFile;


#define DHTTYPE DHT11


DFRobot_DS1307 DS1307;


const int soilPin = A1;
const int solarPin = A0;
const int pumpPin = 5;
const int DHTPin = 4;
const int CSPin = 10;


DHT dht(DHTPin, DHTTYPE);


int debug = 1;
bool pumpOn = false;


void setup() {
    pinMode(soilPin, INPUT);
    pinMode(solarPin, INPUT);
    pinMode(pumpPin, OUTPUT);
    pinMode(CSPin, OUTPUT);
   
    Serial.begin(9600);


    dht.begin();

  
  // Serial.print("Initializing SD card...");
  
  // if (!SD.begin(CSPin)) 
  // {
  //   Serial.println("initialization failed!");
  //   return;

  // }

  // Serial.println("initialization done.");
 
  
  while( !(DS1307.begin()) )
  {
    Serial.println("Communication with device failed, please check connection");
    delay(3000);

  }

  Serial.println("Begin ok!");
  DS1307.setTypeTime(DS1307.eYR, 2000);
  Serial.print("get type time: ");
  Serial.println(DS1307.getTypeTime(DS1307.eYR));
  DS1307.stop();
  uint16_t setTimeBuff[7] = {55, 1, 16, 3, 28, 5, 2025};
                        //  sec min hr dow date mth year
  DS1307.setTime(setTimeBuff);
  DS1307.start();
  DS1307.setSqwPinMode(DS1307.eSquareWave_1Hz);
}


void loop() {
  uint16_t getTimeBuff[7] = {0};
  int mins;
  
  RTC(getTimeBuff);
  mins = getTimeBuff[0];
  if (mins == 0 || pumpOn)
  {
  // SDReader();
      long soilM = Soil();
      float solarData = Light();
      float temperature = Temp();
      float humidity = Humid();
  
  
  float lightLevel = solarData * 5 / 1023 * 1000;
  long mostureValue = map(soilM, 0 ,1023, 0, 100);
  
   delay(1000);
  if (debug){
    Serial.print(mostureValue);
    Serial.println("% moisture");
    Serial.print(lightLevel);
    Serial.println("mV");
    Serial.print((float)humidity,1);
    Serial.println("% humidity");
    Serial.print((float)temperature,1);
    Serial.println("C");

    delay(500);
    }
    pumpOn = mostureValue < 30;
  }
   DCPump(pumpOn);
}




long Soil(){
  long value = analogRead(soilPin);
  return value;
}


void DCPump(bool pumpOn) {
   if(pumpOn) {
   digitalWrite(pumpPin, HIGH);
  }
  else 
   {
      digitalWrite(pumpPin, LOW);
   }
 
}


float Temp() {
  float temp = dht.readTemperature();
  return temp;
}


float Humid() {
  float humid = dht.readHumidity();
  return humid;
}


float Light() {
  float Light = analogRead(solarPin);
  return Light;
}


void RTC( uint16_t getTimeBuff[7]) {
 if(DS1307.eSquareWave_1Hz == DS1307.getSqwPinMode()){
  //Serial.print("SQW/OUT pin: 1Hz | ");
  DS1307.getTime(getTimeBuff);
  char outputarr[128];
  sprintf(outputarr, "time: %04d/%02d/%02d %02d:%02d:%02d\r\n",
            getTimeBuff[6],
            getTimeBuff[5],
            getTimeBuff[4],
            getTimeBuff[2],
            getTimeBuff[1],
            getTimeBuff[0]
            );
  //Serial.println(outputarr);
  }
}


void SDReader() {
    myFile = SD.open("test.txt", FILE_WRITE);

     if (!myFile) 
     {
       Serial.println("error opening test.txt");
        return;
     }
    Serial.print("Writing to test.txt...");

    myFile.println("testing 1, 2, 3.");

  // close the file:

    myFile.close();

    Serial.println("done.");
}


