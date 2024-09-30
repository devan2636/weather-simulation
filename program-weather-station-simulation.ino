//[1] Identitas Pembuat Coding
/**
* [Project 2021]
* 
* Generate by :
*           1.Devandri Suherman
*           Student Electronics Engineering Departement, Bandung State of Polytechnic(1)
* Notes     : Automatic ON-OFF using Telegram BOT
* Copyright 2021
*/

//Program pada Arduino IDE
// Devandri Suherman
// 191354007
#include <Blynk.h>
#define BLYNK_PRINT DebugSerial
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2,3);
//blynk autentik
#include <BlynkSimpleStream.h>
char auth[] = "Y28jsvSpYiFftIRqk-cUszv5WdeFEZZQ" ;
//Komunikasi I2C
#include "Arduino.h"
#include "PCF8591.h"
#define PCF8591_I2C_ADDRESS 0x48
PCF8591 pcf8591 (PCF8591_I2C_ADDRESS);
//Sensor DHT11 Kelembaban
#include "DHT.h"
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
//
int ketinggian,preasure,temp;
int kelembaban;
// menambahkan maps
WidgetMap myMap(V4);
void setup() {
// put your setup code here, to run once:
DebugSerial.begin(9600);
pcf8591.begin();
dht.begin();
Serial.begin(9600);
Blynk.begin(Serial, auth);
//lokasi rumah , Kp. Margahayu
int index = 0 ;
float lat = -7.47856;
float lon = 108.209017;
myMap.location(index,lat,lon, "LOKASI PEMANTAUAN CUACA");
}
void loop() {
// put your main code here, to run repeatedly:
Blynk.run();
//mengukur tekanan udara
preasure = pcf8591.analogRead(AIN1);
float P = map(preasure,0,255,300,1100); //1 millibar [mbar] = 1 hectopascal [hPa]
//mengukur suhu
temp = pcf8591.analogRead(AIN2);
float T = map(temp,0,255,0,65); //rentang suhu antara 0 - 65 derajat Celcius
//menghitung ketinggian
float h = (1013.5 - P)*100;
//mengukur kelembaban
kelembaban = dht.readHumidity();
//mengirim data
Blynk.virtualWrite(0,h); //virtual input V0 di blynk sebagai ketinggian
Blynk.virtualWrite(1,P); //virtual input V1 di blynk sebagai tekanan udara
Blynk.virtualWrite(2,T); //virtual input V2 di blynk sebagai temperature
Blynk.virtualWrite(3,kelembaban); //virtual input V3 di blynk sebagai kelembaban
delay(1000);
}
