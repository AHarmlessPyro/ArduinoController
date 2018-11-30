#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!

#ifndef COMM_H
//#include "comm.h"
#endif

// i2c
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

char sendEntire[10];
char sendOne[6];

#define LSM9DS1_SCK A5
#define LSM9DS1_MISO 12
#define LSM9DS1_MOSI A4
#define LSM9DS1_XGCS 6
#define LSM9DS1_MCS 5
// You can also use software SPI
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS, LSM9DS1_MCS);
// Or hardware SPI! In this case, only CS pins are passed in
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_XGCS, LSM9DS1_MCS);


void setupSensor()
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_12GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_16GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_2000DPS);
}


void setup()
{
  Serial.begin(38400);

  while (!Serial) {
    delay(1); // will pause Zero, Leonardo, etc until serial console opens
  }
  
  Serial.println(F("LSM9DS1 data read demo"));
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println(F("Oops ... unable to initialize the LSM9DS1. Check your wiring!"));
    while (1);
  }
  Serial.println(F("Found LSM9DS1 9DOF"));

  // helper to just set the default scaling we want, see above!
  setupSensor();
  //while(1) loop();
}

void loop() 
{
  if(!Serial){
      Serial.end();
      Serial.begin(38400);
    }
  
  /* Get a new sensor event */ 
  if(Serial.available()){
    lsm.read();  /* ask it to read in the data */ 
    int sensor = Serial.read();
    int orient = Serial.read();
    //Serial.println(sensor);
    //Serial.println(orient);
    sensors_event_t a, m, g, temp;   
    switch(sensor){
        case 'A' : 
          lsm.getEvent(&a, 0, 0, 0); 
          if(orient == -1||orient == '0'){
              Serial.print(a.acceleration.x/*,HEX*/);
              Serial.print(a.acceleration.y/*,HEX*/);
              Serial.println(a.acceleration.z/*,HEX*/);
            }else if(orient == 'X'){
              Serial.println(a.acceleration.x/*,HEX*/);              
            }else if(orient == 'Y'){
              Serial.println(a.acceleration.y/*,HEX*/);              
            }else if(orient == 'Z'){
              Serial.println(a.acceleration.z/*,HEX*/);              
            }
          break;
        case 'G' : 
          lsm.getEvent(0, 0, &g, 0); 
          if(orient == -1||orient == '0'){
              Serial.print(g.gyro.x/*,HEX*/);
              Serial.print(g.gyro.y/*,HEX*/);
              Serial.println(g.gyro.z/*,HEX*/); 
            }else if(orient == 'X'){
              Serial.println(g.gyro.x/*,HEX*/);
            }else if(orient == 'Y'){
              Serial.println(g.gyro.y/*,HEX*/);
            }else if(orient == 'Z'){
              Serial.println(g.gyro.z/*,HEX*/);
            }
          break;
        case 'M' : 
          lsm.getEvent(0, &m, 0, 0); 
          if(orient == -1||orient == '0'){
              Serial.print(m.magnetic.x/*,HEX*/);
              Serial.print(",");
              Serial.print(m.magnetic.y/*,HEX*/);
              Serial.print(",");
              Serial.println(m.magnetic.z/*,HEX*/);
            }else if(orient == 'X'){
              Serial.println(m.magnetic.x/*,HEX*/);
            }else if(orient == 'Y'){
             Serial.println(m.magnetic.y/*,HEX*/);
            }else if(orient == 'Z'){
              Serial.println(m.magnetic.z/*,HEX*/);
            }
          break;
        case 'E' : 
          lsm.getEvent(&a, &m, &g, &temp); 
          if(orient == -1||orient == '0'){
              Serial.print(a.acceleration.x/*,HEX*/);
              Serial.print(",");
              Serial.print(a.acceleration.y/*,HEX*/);
              Serial.print(",");
              Serial.print(a.acceleration.z/*,HEX*/);
              Serial.print(";");
              Serial.print(m.magnetic.x/*,HEX*/);
              Serial.print(",");
              Serial.print(m.magnetic.y/*,HEX*/);
              Serial.print(",");
              Serial.print(m.magnetic.z/*,HEX*/);
              Serial.print(";");
              Serial.print(g.gyro.x/*,HEX*/);
              Serial.print(",");
              Serial.print(g.gyro.y/*,HEX*/);
              Serial.print(",");
              Serial.println(g.gyro.z/*,HEX*/);
            }else if(orient == 'X'){
              Serial.print(a.acceleration.x/*,HEX*/);
              Serial.print(";");
              Serial.print(m.magnetic.x/*,HEX*/);
              Serial.print(";");
              Serial.println(g.gyro.x/*,HEX*/);
            }else if(orient == 'Y'){
              Serial.print(a.acceleration.y/*,HEX*/);
              Serial.print(";");
              Serial.print(m.magnetic.y/*,HEX*/);
              Serial.print(";");
              Serial.println(g.gyro.y/*,HEX*/);
            }else if(orient == 'Z'){
              Serial.print(a.acceleration.z/*,HEX*/);
              Serial.print(";");
              Serial.print(m.magnetic.z/*,HEX*/);
              Serial.print(";");
              Serial.println(g.gyro.z/*,HEX*/);
            }        
          break;                  
          case 'I':
          lsm.getEvent(&a, &m, &g, &temp); 
          if(orient == -1||orient == '0'){
              Serial.print(a.acceleration.x/*,HEX*/);
              Serial.print(",");
              Serial.print(a.acceleration.y/*,HEX*/);
              Serial.print(",");
              Serial.print(a.acceleration.z/*,HEX*/);
              Serial.print(";");
              Serial.print(m.magnetic.x/*,HEX*/);
              Serial.print(",");
              Serial.print(m.magnetic.y/*,HEX*/);
              Serial.print(",");
              Serial.println(m.magnetic.z/*,HEX*/);
            }else if(orient == 'X'){
              Serial.print(a.acceleration.x/*,HEX*/);
              Serial.print(";");
              Serial.print(m.magnetic.x/*,HEX*/);
            }else if(orient == 'Y'){
              Serial.print(a.acceleration.y/*,HEX*/);
              Serial.print(";");
              Serial.print(m.magnetic.y/*,HEX*/);
            }else if(orient == 'Z'){
              Serial.print(a.acceleration.z/*,HEX*/);
              Serial.print(";");
              Serial.print(m.magnetic.z/*,HEX*/);
            }        
          break;                  
      }        
    //Serial.print("Temp : "); Serial.println(temp.temperature);
    Serial.println();
  }
}
