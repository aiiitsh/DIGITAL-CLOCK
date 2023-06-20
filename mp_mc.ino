#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AM2320.h>

Adafruit_AM2320 am2320;

#define STOP			      0x00
#define FIRE_ALARM		  0x03
#define FIRE_TIMER		  0x09
#define GET_TEMPERATURE	0x12
#define GET_HUMIDITY	  0x15

#define GROUND  10
#define POWER   13
  unsigned long int reading, temperature, humidity, currentMillis, choice = 100;
  unsigned long int previousMillis = 0;
void setup() {
pinMode(GROUND, OUTPUT);
pinMode(POWER, OUTPUT);
digitalWrite(GROUND, LOW);
 Wire.begin();
  Serial.begin(9600);
}

void loop() {
  currentMillis = millis();
  if (currentMillis - previousMillis >= 5000) {
    previousMillis = currentMillis;
    reading = am2320.readRegister32(AM2320_REG_HUM_H);
    temperature = (unsigned short int) reading;
    humidity = (reading >> 16);
    }
    if (Serial.available())
    {
      choice = Serial.read();
      switch(choice)
      {
        case GET_HUMIDITY:
        Serial.write((unsigned char) humidity);
        Serial.write((unsigned char)(humidity >> 8));
        break;
        case GET_TEMPERATURE:
        Serial.write((unsigned char) temperature);
        Serial.write((unsigned char)(temperature >> 8));
        break;
      }
    }
    while(choice == FIRE_ALARM)
    {
      tone(POWER, 2000);
      if (Serial.available())
      {
      choice = Serial.read();
      switch(choice)
      {
        case GET_HUMIDITY:
        Serial.write((unsigned char) humidity);
        Serial.write((unsigned char)(humidity >> 8));
        choice = FIRE_ALARM;
        break;
        case GET_TEMPERATURE:
        Serial.write((unsigned char) temperature);
        Serial.write((unsigned char)(temperature >> 8));
        choice = FIRE_ALARM;
        break;
      }
      }
    }
    while(choice == FIRE_TIMER)
    {
      tone(POWER, 1);
      if (Serial.available())
      {
      choice = Serial.read();
      switch(choice)
      {
        case GET_HUMIDITY:
        Serial.write((unsigned char) humidity);
        Serial.write((unsigned char)(humidity >> 8));
        choice = FIRE_TIMER;
        break;
        case GET_TEMPERATURE:
        Serial.write((unsigned char) temperature);
        Serial.write((unsigned char)(temperature >> 8));
        choice = FIRE_TIMER;
        break;
      }
      }
    }
    noTone(POWER);
}